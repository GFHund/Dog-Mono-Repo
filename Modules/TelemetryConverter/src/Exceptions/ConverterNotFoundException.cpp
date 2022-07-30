#include <Exceptions/ConverterNotFoundException.h>

namespace CTelemetry{
    namespace Converter{
        ConverterNotFoundException::ConverterNotFoundException(std::string converterType){
            this->converterType = converterType;
            this->mMessage = "Converter not Found Exception:"+converterType;
        }
        const char* ConverterNotFoundException::what() const throw(){
            return mMessage.c_str();
        }
    }
}