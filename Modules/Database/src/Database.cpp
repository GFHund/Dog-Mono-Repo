#include <Database.h>
#include <Exceptions/SQLErrorException.h>
#include <Exceptions/TableNotFoundException.h>

namespace DogGE{
    namespace Database{
        Database::Database(sqlite3* db,DatabaseType type){
            this->mDb = db;
            this->mType = type;
            indexTables();
        }
        Database::Database(Database &db){
            this->mDb = db.getRawDatabase();
            this->mType = db.getType();
        }
        Database::~Database(){
            sqlite3_close(this->mDb);
        }
        sqlite3* Database::getRawDatabase(){
            return this->mDb;
        }
        Database::DatabaseType Database::getType(){
            return this->mType;
        }

        bool Database::hasTable(std::string table){
            for(auto cachedTable: this->mTables){
                if(table.compare(cachedTable.tableName) == 0){
                    return true;
                }
            }
            return false;
        }
        //void createTable(AbstractEntity* table);
        void Database::persistData(AbstractEntity* data){
            std::map<std::string,AbstractEntity*> preEntity = data->getNTo1Relations();
            for(auto entityIter:preEntity){
                this->persistData(entityIter.second);
                data->setEntityRelations(entityIter.first,entityIter.second);
            }

            std::vector<std::pair<std::string,Table::DataType>> columns;
            
            try{
                columns = getColumnDefinition(data->getTableName());
            } catch(TableNotFoundException &e){
                //if the table is not in the database than create the table
                createTable(data);
                columns = getColumnDefinition(data->getTableName());
            }
            int dataId = data->getId();
            bool bUpdate = false;
            if(dataId == -1){
                bUpdate = false;
            } else {
                QueryBuilder builder = createQueryBuilder(data->getTableName());
                builder.where("id = @id")->addIntParameter(1,data->getId());
                int numRows = countData(builder);
                bUpdate = numRows > 0;
            }
            
            sqlite3_stmt* stmt;
            std::string sql;
            if(bUpdate){
                std::string updateSql = "UPDATE ";
                updateSql += data->getTableName();
                updateSql += "SET ";
                bool bFirst = true;
                int count = 0;
                for(auto column:columns){
                    if(column.first.compare("id") == 0){
                        continue;
                    }
                    if(bFirst){
                        bFirst = false;
                    } else {
                        updateSql += ",";
                    }
                    updateSql += column.first;
                    updateSql += " = @";
                    updateSql += std::to_string(count);
                    count++;
                }
                updateSql += " WHERE id = @Id;";
                if(sqlite3_prepare_v2(this->mDb,updateSql.c_str(),updateSql.size(),&stmt,NULL) != SQLITE_OK){
                    std::string error = std::string(sqlite3_errmsg(this->mDb));
                    throw SQLErrorException(error,updateSql);
                }
                sql = updateSql;
            } else {
                std::string insertSql = "INSERT INTO ";
                insertSql += data->getTableName();
                insertSql += "(";
                bool bFirst = true;
                for(auto column:columns){
                    if(column.first.compare("id") == 0){
                        continue;
                    }
                    if(bFirst){
                        bFirst = false;
                    } else {
                        insertSql += ",";
                    }
                    insertSql +=column.first;
                }
                insertSql += ") VALUES (";
                int count = 0;
                bFirst = true;
                for(auto column:columns){
                    if(column.first.compare("id") == 0){
                        continue;
                    }
                    if(bFirst){
                        bFirst = false;
                    } else {
                        insertSql += ",";
                    }
                    insertSql += "@";
                    insertSql += std::to_string(count);
                    count++;
                }
                insertSql += ");";
                if(sqlite3_prepare_v2(this->mDb,insertSql.c_str(),insertSql.size(),&stmt,NULL) != SQLITE_OK){
                    std::string error = std::string(sqlite3_errmsg(this->mDb));
                    throw SQLErrorException(error,insertSql);
                }
                sql = insertSql;
            }

            std::map<std::string,int> intValues = data->getIntMap();
            std::map<std::string,float> floatValues = data->getRealMap();
            std::map<std::string,std::string> stringValues = data->getStringMap();
            std::map<std::string,std::pair<char*,int>> rawValues = data->getRawMap();
            int count=1;
            for(auto column:columns){
                if(column.first.compare("id") == 0){
                    continue;
                }
                switch(column.second){
                    case Table::DATATYPE_INT:{
                        auto it = intValues.find(column.first);
                        sqlite3_bind_int(stmt,count,it->second);
                        break;
                    }
                    case Table::DATATYPE_INT64:{
                        auto it = intValues.find(column.first);
                        sqlite3_bind_int64(stmt,count,it->second);
                        break;
                    }
                    case Table::DATATYPE_REAL:{
                        auto it = floatValues.find(column.first);
                        sqlite3_bind_double(stmt,count,it->second);
                        break;
                    }
                    case Table::DATATYPE_STRING:{
                        auto it = stringValues.find(column.first);
                        sqlite3_bind_text(stmt,count,it->second.c_str(),it->second.size(),SQLITE_TRANSIENT);
                        break;
                    }
                    case Table::DATATYPE_RAW:{
                        auto it = rawValues.find(column.first);
                        sqlite3_bind_blob(stmt,count,it->second.first,it->second.second,SQLITE_TRANSIENT);
                    }
                }
                count++;
            }
            if(bUpdate){
                sqlite3_bind_int(stmt,count,data->getId());
            }
            int rc = sqlite3_step(stmt);

            if(rc == SQLITE_DONE || rc == SQLITE_OK){
                sqlite3_finalize(stmt);
            } else {
                std::string error = std::string(sqlite3_errmsg(this->mDb));
                sqlite3_finalize(stmt);
                throw SQLErrorException(error,sql);
            }
            std::map<std::string,std::vector<AbstractEntity*>> postEntities = data->get1ToNRelations();
            for(auto iterEntities:postEntities){
                for(auto iterEntity:iterEntities.second){
                    iterEntity->setEntityRelations(data->getTableName(),data);
                    this->persistData(iterEntity);
                    
                    //data->setEntityRelations(iterEntities.first,iterEntity);
                }
                
            }
        }

        QueryBuilder Database::createQueryBuilder(std::string table){
            for(auto indexedTables:this->mTables){
                if(table.compare(indexedTables.tableName) == 0){
                    return QueryBuilder(indexedTables);
                }
            }
            throw TableNotFoundException(table);
        }

        

        int Database::countData(QueryBuilder query){
            std::string countSql = query.buildCountSql();
            sqlite3_stmt* stmt;
            if(sqlite3_prepare_v2(this->mDb,countSql.c_str(),countSql.size(),&stmt,NULL) != SQLITE_OK){
                std::string error = std::string(sqlite3_errmsg(this->mDb));
                throw SQLErrorException(error,countSql);
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
            int ret_code = sqlite3_step(stmt);
            if(ret_code == SQLITE_ROW || ret_code == SQLITE_OK || ret_code == SQLITE_DONE){
                int numRows = sqlite3_column_int(stmt,0);
                sqlite3_finalize(stmt);
                return numRows;
            }
            std::string error = std::string(sqlite3_errmsg(this->mDb));
            sqlite3_finalize(stmt);
            throw SQLErrorException(error,countSql);
        }

        void Database::indexTables(){
            std::string getTablesSql = "SELECT name FROM sqlite_schema WHERE type='table' AND name NOT LIKE 'sqlite_%';";
            
            sqlite3_stmt* stmt;
            if(sqlite3_prepare_v2(this->mDb,getTablesSql.c_str(),getTablesSql.size(),&stmt,NULL) != SQLITE_OK){
                std::string error = std::string(sqlite3_errmsg(this->mDb));
                throw SQLErrorException(error,getTablesSql);
            }
            int ret_code;
            std::list<std::string> tableNames;
            while((ret_code = sqlite3_step(stmt)) == SQLITE_ROW){
                std::string name = (const char*)sqlite3_column_text(stmt,0);
                tableNames.push_back(name);
            }
            sqlite3_finalize(stmt);

            for(auto indexedTables:this->mTables){
                bool bAlreadyIndexed = false;
                int position = 0;
                for(auto table:tableNames){
                    if(table.compare(indexedTables.tableName) == 0){
                        bAlreadyIndexed = true;
                        break;
                    }
                    position++;
                }
                std::list<std::string>::iterator it;
                it = tableNames.begin();
                advance(it,position);
                tableNames.erase(it);
            }

            for(auto table:tableNames){
                std::string getColumns = "PRAGMA table_info(";
                getColumns += table;
                getColumns += ");";
                if(sqlite3_prepare_v2(this->mDb,getColumns.c_str(),getColumns.size(),&stmt,NULL) != SQLITE_OK){
                    std::string error = std::string(sqlite3_errmsg(this->mDb));
                    throw SQLErrorException(error,getColumns);
                }
                std::vector<std::pair<std::string,Table::DataType>> columns;
                while((ret_code = sqlite3_step(stmt)) == SQLITE_ROW){
                    std::string name = (const char*)sqlite3_column_text(stmt,1);
                    std::string type = (const char*)sqlite3_column_text(stmt,2);
                    if(type.compare("INTEGER") == 0){
                        columns.push_back(std::make_pair(name,Table::DATATYPE_INT));
                    } else if(type.compare("BIGINT") == 0){
                        columns.push_back(std::make_pair(name,Table::DATATYPE_INT64));
                    } else if(type.compare("REAL") == 0){
                        columns.push_back(std::make_pair(name,Table::DATATYPE_REAL));
                    } else if(type.compare("BLOB") == 0){
                        columns.push_back(std::make_pair(name,Table::DATATYPE_RAW));
                    } else if(type.compare("TEXT") == 0){
                        columns.push_back(std::make_pair(name,Table::DATATYPE_STRING));
                    }
                }
                sqlite3_finalize(stmt);
                Table newTable;
                newTable.tableName = table;
                newTable.columns = columns;
                this->mTables.push_back(newTable);
            }
        }

        std::vector<std::pair<std::string,Table::DataType>> Database::getColumnDefinition(std::string table){
            for(auto indexedTables:this->mTables){
                if(table.compare(indexedTables.tableName) == 0){
                    return indexedTables.columns;
                }
            }
            throw TableNotFoundException(table);
        }
        void Database::createTable(AbstractEntity* table){
            std::string sql = table->getTableDefinition();
            sqlite3_stmt* stmt;
            if(sqlite3_prepare_v2(this->mDb,sql.c_str(),sql.size(),&stmt,NULL) != SQLITE_OK){
                std::string error = std::string(sqlite3_errmsg(this->mDb));
                throw SQLErrorException(error,sql);
            }
            int ret_code = sqlite3_step(stmt);
            if(ret_code == SQLITE_DONE){
                sqlite3_finalize(stmt);
                indexTables();
                return;
            }
            std::string error = std::string(sqlite3_errmsg(this->mDb));
            sqlite3_finalize(stmt);
            throw SQLErrorException(error,sql);
        }
        PrepareStatement* Database::prepareStatement(std::string sql){
            sqlite3_stmt* stmt;
            if(sqlite3_prepare_v2(this->mDb,sql.c_str(),sql.size(),&stmt,NULL) != SQLITE_OK){
                std::string error = std::string(sqlite3_errmsg(this->mDb));
                throw SQLErrorException(error,sql);
            }
            return new PrepareStatement(stmt);
        }
    }
}