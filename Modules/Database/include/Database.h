#ifndef __DATABASE__
#define __DATABASE__

#include "../vendor/sqlite3/sqlite3.h"
#include <AbstractEntity.h>
#include <QueryBuilder.h>
#include <PrepareStatement.h>
#include <vector>
#include <string>
#include <Table.h>
#include <list>
#include <type_traits>
#include <Exceptions/SQLErrorException.h>

namespace DogGE{
    namespace Database{

        template<class T>
        concept IsEntity = std::is_base_of<AbstractEntity,T>::value;

        class Database{
            public:
            enum DatabaseType{
                DATABASE_IN_MEMORY,
                DATABASE_FILE
            };
            private:
            sqlite3* mDb;
            DatabaseType mType;
            std::vector<Table> mTables; 

            protected:
            void indexTables();
            std::vector<std::pair<std::string,Table::DataType>> getColumnDefinition(std::string table);
            void createTable(AbstractEntity* table);

            public:

            template<IsEntity T>
            struct ResultIterator{
                public:
                using iterator_category = std::forward_iterator_tag;
                using difference_type = T;
                using value_type = T;
                using pointer = T*;
                using reference = T&;
                ResultIterator(sqlite3_stmt* stmt,int result,int numRows);
                ~ResultIterator();
                
                ResultIterator&  operator++();
                
                T& operator*();
                T* operator->();

                bool isError();
                std::string getError();
                bool isEnd();
                
                
                private:
                void buildObject();
                sqlite3_stmt* mStmt;
                int mResult;
                int mNumRows;
                T mEntity;
            };
            enum ColumnType{
                COLUMN_TYPE_STRING,
                COLUMN_TYPE_INT,
                COLUMN_TYPE_REAL,
                COLUMN_TYPE_RAW
            };

            Database(sqlite3* db,DatabaseType type);
            Database(Database &db);
            ~Database();
            sqlite3* getRawDatabase();
            DatabaseType getType();
            bool hasTable(std::string table);
            
            void persistData(AbstractEntity* data);
            QueryBuilder createQueryBuilder(std::string table);
            template<IsEntity T>
            std::vector<T*> selectAllData(QueryBuilder query);
            template<IsEntity T>
            Database::ResultIterator<T> selectData(QueryBuilder query);
            int countData(QueryBuilder query);
            PrepareStatement* prepareStatement(std::string sql);
        };

        template<IsEntity T>
        Database::ResultIterator<T>::ResultIterator(sqlite3_stmt* stmt,int result,int numRows){
            this->mStmt = stmt;
            this->mResult = result;
            this->mNumRows = numRows;
            this->buildObject();
        }
        template<IsEntity T>
        Database::ResultIterator<T>::~ResultIterator(){
            sqlite3_finalize(this->mStmt);
        }
        template<IsEntity T>
        Database::ResultIterator<T>& Database::ResultIterator<T>::operator++(){
            int ret_code;
            ret_code = sqlite3_step(this->mStmt);
            this->mResult = ret_code;
            if(this->mResult != SQLITE_OK && this->mResult != SQLITE_ROW){
                return *this;
            }
            this->buildObject();
            return *this;
        }
        template<IsEntity T>
        T& Database::ResultIterator<T>::operator*(){
            return mEntity;
        }
        template<IsEntity T>
        T* Database::ResultIterator<T>::operator->(){
            return &mEntity;
        }

        template<IsEntity T>
        void Database::ResultIterator<T>::buildObject(){
            T entity;
            int numColumns = sqlite3_column_count(mStmt);
            for(int i=0;i < numColumns;i++){
                const char* columnName = sqlite3_column_origin_name(mStmt,i);
                std::string columnNameStr(columnName);
                int type = sqlite3_column_type(mStmt,i);
                
                if(type == SQLITE_INTEGER){
                    int value = sqlite3_column_int(mStmt,i);
                    entity.matchIntData(columnNameStr,value);
                } else if(type == SQLITE_FLOAT){
                    float value = sqlite3_column_double(mStmt,i);
                    entity.matchRealData(columnNameStr,value);
                } else if(type == SQLITE_TEXT){
                    std::string str = std::string((const char*)sqlite3_column_text(mStmt,i));
                    entity.matchStringData(columnNameStr,str);
                }
            }
            mEntity = entity;
        }
        template<IsEntity T>
        bool Database::ResultIterator<T>::isError(){
            //return !(this->mResult == SQLITE_OK || this->mResult == SQLITE_ROW || this->mResult != );
            return this->mResult == SQLITE_ERROR;
        }
        template<IsEntity T>
        std::string Database::ResultIterator<T>::getError(){
            return sqlite3_errmsg(this->mDb);
        }
        template<IsEntity T>
        bool Database::ResultIterator<T>::isEnd(){
            return this->mResult == SQLITE_OK || this->mResult == SQLITE_DONE;
        }

        template<IsEntity T>
        std::vector<T*> Database::selectAllData(QueryBuilder query){
            int rowCount = this->countData(query);
            if(rowCount <= 0){
                return std::vector<T*>();    
            }
            std::string sql = query.buildSql();
            sqlite3_stmt* stmt;
            if(sqlite3_prepare_v2(this->mDb,sql.c_str(),sql.size(),&stmt,NULL) != SQLITE_OK){
                throw SQLErrorException(sqlite3_errmsg(this->mDb),sql);
            }

            int parameterCount = query.getParameterCount();
            if(parameterCount > 0){
                std::map<int,int> intParameter = query.getIntParameters();
                std::map<int,int64_t> int64Parameter = query.getInt64Parameters();
                std::map<int,float> realParameter = query.getRealParameters();
                std::map<int,std::string> textParameter = query.getTextParameters();
                std::map<int,std::pair<char*,int>> rawParameter = query.getRawParameters();
                for(int i=1;i<=parameterCount;i++){
                    auto intIter = intParameter.find(i);
                    if(intIter != intParameter.end()){
                        sqlite3_bind_int(stmt,i,intIter->second);
                    }

                    auto int64Iter = int64Parameter.find(i);
                    if(int64Iter != int64Parameter.end()){
                        sqlite3_bind_int64(stmt,i,int64Iter->second);
                    }

                    auto realIter = realParameter.find(i);
                    if(realIter != realParameter.end()){
                        sqlite3_bind_double(stmt,i,realIter->second);
                    }

                    auto textIter = textParameter.find(i);
                    if(textIter != textParameter.end()){
                        sqlite3_bind_text(stmt,i,textIter->second.c_str(),textIter->second.size(),SQLITE_TRANSIENT);
                    }

                    auto rawIter = rawParameter.find(i);
                    if(rawIter != rawParameter.end()){
                        sqlite3_bind_blob(stmt,i,rawIter->second.first,rawIter->second.second,SQLITE_TRANSIENT);
                    }
                }
            }

            std::vector<T*> ret(rowCount,nullptr);
            int ret_code;
            int rowPointer = 0;
            while((ret_code = sqlite3_step(stmt)) == SQLITE_ROW){
                int numColumns = sqlite3_column_count(stmt);
                
                T* newEntity = new T();
                for(int i=0;i<numColumns;i++){
                    const char* columnName = sqlite3_column_origin_name(stmt,i);
                    std::string columnNameStr(columnName);
                    const char* typeStrRaw = sqlite3_column_decltype(stmt,i);
                    std::string typeStr(typeStrRaw);
                    int type = sqlite3_column_type(stmt,i);
                    
                    if(type == SQLITE_INTEGER){
                        int value = sqlite3_column_int(stmt,i);
                        int64_t value64 = sqlite3_column_int64(stmt,i);
                        if(value == value64){
                            newEntity->matchIntData(columnNameStr,value);
                        } else {
                            newEntity->matchInt64Data(columnNameStr,value64);
                        }
                    } else if(type == SQLITE_FLOAT){
                        float value = sqlite3_column_double(stmt,i);
                        newEntity->matchRealData(columnNameStr,value);
                    } else if(type == SQLITE_TEXT){
                        const unsigned char* strRaw = sqlite3_column_text(stmt,i);
                        std::string str = std::string((const char*) strRaw);
                        newEntity->matchStringData(columnNameStr,str);
                    }
                }
                if(rowPointer >= ret.size()){
                    break;
                }
                ret[rowPointer] = newEntity;
                rowPointer++;
            }
            sqlite3_finalize(stmt);
            return ret;
        }

        template<IsEntity T>
        Database::ResultIterator<T> Database::selectData(QueryBuilder query){
            int rowCount = this->countData(query);
            std::string sql = query.buildSql();
            sqlite3_stmt* stmt;
            if(sqlite3_prepare_v2(this->mDb,sql.c_str(),sql.size(),&stmt,NULL) != SQLITE_OK){
                throw SQLErrorException(sqlite3_errmsg(this->mDb),sql);
            }

            int parameterCount = query.getParameterCount();
            if(parameterCount > 0){
                std::map<int,int> intParameter = query.getIntParameters();
                std::map<int,float> realParameter = query.getRealParameters();
                std::map<int,std::string> textParameter = query.getTextParameters();
                std::map<int,std::pair<char*,int>> rawParameter = query.getRawParameters();
                for(int i=1;i<=parameterCount;i++){
                    auto intIter = intParameter.find(i);
                    if(intIter != intParameter.end()){
                        sqlite3_bind_int(stmt,i,intIter->second);
                    }

                    auto realIter = realParameter.find(i);
                    if(realIter != realParameter.end()){
                        sqlite3_bind_double(stmt,i,realIter->second);
                    }

                    auto textIter = textParameter.find(i);
                    if(textIter != textParameter.end()){
                        sqlite3_bind_text(stmt,i,textIter->second.c_str(),textIter->second.size(),SQLITE_TRANSIENT);
                    }

                    auto rawIter = rawParameter.find(i);
                    if(rawIter != rawParameter.end()){
                        sqlite3_bind_blob(stmt,i,rawIter->second.first,rawIter->second.second,SQLITE_TRANSIENT);
                    }
                }
            }

            int retCode = sqlite3_step(stmt);

            return Database::ResultIterator<T>(stmt,retCode,rowCount);
        }
    }
}



#endif 