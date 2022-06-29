#ifndef __DATABASE_NOT_FOUND_EXCEPTION__
#define __DATABASE_NOT_FOUND_EXCEPTION__

#include <exception>
#include <string>
namespace DogGE{
    namespace Database{
        class DatabaseNotFoundException{
            private:
            std::string mFile;
            std::string mMessage;
            public:
            DatabaseNotFoundException(std::string file);
            const char* what() const throw();
        };
    }
}

#endif