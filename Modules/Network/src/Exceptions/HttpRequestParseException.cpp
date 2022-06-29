#include <Exceptions/HttpRequestParseException.h>

namespace DogGE{
    namespace Network{
        HttpRequestParseException::HttpRequestParseException(std::string part,char Character){
            this->mPart = part;
            this->mChar = "";
            this->mChar += Character;
            this->mMessage = "Error: HTTP Parse Exception Unexpected char " + this->mChar + " near "+part;
        }
        const char* HttpRequestParseException::what() const throw(){
            return this->mMessage.c_str();
        }
    }
}