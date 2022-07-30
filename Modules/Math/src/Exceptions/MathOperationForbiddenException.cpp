#include <Exceptions/MathOperationForbiddenException.h>
#include <cstring>
namespace DogGE{
    namespace Math{
        MathOperationForbiddenException::MathOperationForbiddenException(std::string message){
            this->mMessage = message;
        }

        const char* MathOperationForbiddenException::what() const throw(){
            std::string message = "Math Operation Forbidden: ";
            message += this->mMessage;
            char* ret = new char[message.size()];
            strcpy(ret,message.c_str());
            return ret;//ret.c_str();
        }
    }
}


