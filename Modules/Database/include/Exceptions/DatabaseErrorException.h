#ifndef __DATABASE_ERROR_EXCEPTION__
#define __DATABASE_ERROR_EXCEPTION__

#include <exception>
#include <string>

namespace DogGE{
    namespace Database{
        class DatabaseErrorException:public std::exception{
            private:
            std::string mMessage;
            public:
            DatabaseErrorException(std::string reason);
            const char* what() const throw();
        };
    }
}

#endif