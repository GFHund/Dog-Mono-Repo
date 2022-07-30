#include <Exceptions/UnsupportedConvertException.h>

namespace DogGE{
    namespace Image{
        UnsupportedConvertException::UnsupportedConvertException(unsigned int from,unsigned int to){
            this->mFromColorType = from;
            this->mToColorType = to;
            this->mMessage = "Could not convert from ";
            this->mMessage += std::to_string(from);
            this->mMessage += " to ";
            this->mMessage += std::to_string(to);
        }
        const char* UnsupportedConvertException::what()const throw(){
            return this->mMessage.c_str();
        }
    }
}