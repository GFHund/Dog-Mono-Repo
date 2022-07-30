#ifndef __CONVERTER_NOT_SUITABLE__
#define __CONVERTER_NOT_SUITABLE__
#pragma once

#include <exception>
#include <string>

namespace CTelemetry{
    namespace Converter{
        class ConverterNotSuitable:public std::exception{
            private:
            std::string mMessage;
            public:
            ConverterNotSuitable();
            virtual const char* what() const throw();
        };
    }
}

#endif