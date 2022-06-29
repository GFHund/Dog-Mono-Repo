#include <Exceptions/ConvertErrorException.h>

namespace DogGE{
    namespace Database{
        ConvertErrorException::ConvertErrorException(std::string reason){
            this->mMessage = "Error at Converting Database: ";
            this->mMessage += reason;
        }
        const char* ConvertErrorException::what() const throw(){
            return this->mMessage.c_str();
        }
    }
}