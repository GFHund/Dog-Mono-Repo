#ifndef __TABLE_NOT_FOUND_EXCEPTION__
#define __TABLE_NOT_FOUND_EXCEPTION__

#include <exception>
#include <string>

namespace DogGE{
    namespace Database{
        class TableNotFoundException:public std::exception{
            private:
            std::string mTableName;
            std::string mMessage;
            public:
            TableNotFoundException(std::string tablename);
            const char* what() const throw();
        };
    }
}

#endif