#ifndef __CONVERT_ERROR_EXCEPTION__
#define __CONVERT_ERROR_EXCEPTION__

#include <exception>
#include <string>

namespace DogGE{
    namespace Database{
        class ConvertErrorException:public std::exception{
            private:
            std::string mMessage;
            public:
            ConvertErrorException(std::string reason);
            const char* what() const throw();
        };
    }
}

#endif