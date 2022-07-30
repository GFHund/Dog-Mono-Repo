#ifndef __CONVERT_DATA_TYPE_EXCEPTION__
#define __CONVERT_DATA_TYPE_EXCEPTION__

#include <exception>
#include <string>

namespace DogGE{
    namespace Json{
        class ConvertDataTypeException:public std::exception{
            private:
            std::string mFromType;
            std::string mToType;
            std::string mMessage;
            public:
            ConvertDataTypeException(std::string fromType,std::string toType);
            virtual const char* what() const throw();
        };
    }
}

#endif