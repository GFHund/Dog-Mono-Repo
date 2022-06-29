#include <Exceptions/SQLErrorException.h>

namespace DogGE{
    namespace Database{
        SQLErrorException::SQLErrorException(std::string errorMsg,std::string sql){
            this->mSql = sql;
            this->mErrorMsg = errorMsg;
            this->mMessage = "Error: ";
            this->mMessage += errorMsg;
            this->mMessage += " SQL: ";
            this->mMessage += sql;
        }
        const char* SQLErrorException::what() const throw(){
            return this->mMessage.c_str();
        }
        std::string SQLErrorException::getSql(){
            return this->mSql;
        }
        std::string SQLErrorException::getErrorMsg(){
            return this->mErrorMsg;
        }
    }
}