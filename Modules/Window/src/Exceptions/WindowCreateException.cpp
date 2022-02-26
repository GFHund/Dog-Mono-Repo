#include <Exceptions/WindowCreateException.h>

namespace DogGE{
    namespace Window{
        WindowCreateException::WindowCreateException(std::string message){
            this->mMessage = message;
        }
        const char* WindowCreateException::what() const throw(){
            return this->mMessage.c_str();
        }
    }
}