#include <Exceptions/ConverterNotSuitable.h>

namespace CTelemetry{
    namespace Converter{
        ConverterNotSuitable::ConverterNotSuitable(){
            this->mMessage = "Converter not Suitable";
        }
        const char* ConverterNotSuitable::what() const throw(){
            return this->mMessage.c_str();
        }
    }
}