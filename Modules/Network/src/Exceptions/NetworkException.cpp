#include <Exceptions/NetworkException.h>

namespace DogGE{
    namespace Network{
        NetworkException::NetworkException(int errorCode){
            this->mErrorCode = errorCode;
            this->mMessage = "Error: Connection throws Error Code: ";
            this->mMessage += std::to_string(errorCode);
        }
        const char* NetworkException::what() const throw(){
            return this->mMessage.c_str();
        }
    }
}