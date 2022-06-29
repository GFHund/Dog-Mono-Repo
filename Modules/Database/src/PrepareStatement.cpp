#include <PrepareStatement.h>
#include <Exceptions/DatabaseErrorException.h>

namespace DogGE{
    namespace Database{
        PrepareStatement::PrepareStatement(sqlite3_stmt* stmt){
            this->mStmt = stmt;
        }
        PrepareStatement::~PrepareStatement(){
            sqlite3_finalize(this->mStmt);
        }
        void PrepareStatement::setIntParam(int colpos,int value){
            sqlite3_bind_int(this->mStmt,colpos,value);
        }
        void PrepareStatement::setInt64Param(int colpos,int64_t value){
            sqlite3_bind_int64(this->mStmt,colpos,value);
        }
        void PrepareStatement::setFloatParam(int colpos,float value){
            sqlite3_bind_double(this->mStmt,colpos,value);
        }
        void PrepareStatement::setBlobParam(int colpos,char* data,int size){
            sqlite3_bind_blob(this->mStmt,colpos,data,size,SQLITE_TRANSIENT);
        }
        void PrepareStatement::resetParam(){
            sqlite3_clear_bindings(this->mStmt);
			sqlite3_reset(this->mStmt);
        }
        /**
         * @brief Not for select statements
         * 
         */
        void PrepareStatement::execute(){
            int rc = sqlite3_step(this->mStmt);
            if(rc != SQLITE_DONE){
                throw DatabaseErrorException("Error at execute database command");
            }
        }
        bool PrepareStatement::fetch(){
            int rc = sqlite3_step(this->mStmt);
            if(rc == SQLITE_ROW){
                return true;
            } else if(rc == SQLITE_DONE){
                return false;
            } else {
                throw DatabaseErrorException("Error at fetch Rows");
            }
        }
        int PrepareStatement::readIntValue(unsigned int column){
            return sqlite3_column_int(this->mStmt,column);
        }
        int64_t PrepareStatement::readInt64Value(unsigned int column){
            return sqlite3_column_int64(this->mStmt,column);
        }
        float PrepareStatement::readFloatValue(unsigned int column){
            return sqlite3_column_double(this->mStmt,column);
        }
        std::string PrepareStatement::readStringValue(unsigned int column){
            const char* ret = (const char*)sqlite3_column_text(this->mStmt,column);
            return std::string(ret);
        }
    }
}