#ifndef __SQL_ERROR_EXCEPTION__
#define __SQL_ERROR_EXCEPTION__

#include <exception>
#include <string>

namespace DogGE{
    namespace Database{
        class SQLErrorException:public std::exception{
            private:
            std::string mSql;
            std::string mErrorMsg;
            std::string mMessage;
            public:
            SQLErrorException(std::string errorMsg,std::string sql);
            const char* what() const throw();
            std::string getSql();
            std::string getErrorMsg();
        };
    }
}

#endif