#ifndef __CONVERTER_NOT_FOUND_EXCEPTION__
#define __CONVERTER_NOT_FOUND_EXCEPTION__
#pragma once

#include <exception>
#include <string>

namespace CTelemetry{
    namespace Converter{
        class ConverterNotFoundException: public std::exception{
            private:
            std::string mMessage;
            std::string converterType;
            public:
            ConverterNotFoundException(std::string requestedConverterType);
            virtual const char* what() const throw();
        };
    }
}
#endif