#ifndef __UNSUPPORTED_CONVERT_EXCEPTION__
#define __UNSUPPORTED_CONVERT_EXCEPTION__
#pragma once

#include <exception>
#include <string>

namespace DogGE{
    namespace Image{
        class UnsupportedConvertException:public std::exception{
            private:
            std::string mMessage;
            unsigned int mFromColorType;
            unsigned int mToColorType;
            public:
            UnsupportedConvertException(unsigned int from,unsigned int to);
            const char* what()const throw();
        };
    }
}

#endif