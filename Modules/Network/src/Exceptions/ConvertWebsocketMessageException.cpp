#include <Exceptions/ConvertWebsocketMessageException.h>

namespace DogGE{
    namespace Network{
        ConvertWebsocketMessageException::ConvertWebsocketMessageException(std::string message){
            this->mMessage = message;
        }
        const char* ConvertWebsocketMessageException::what() const throw(){
            return this->mMessage.c_str();
        }
    }
}