#include <Exceptions/DatabaseErrorException.h>

namespace DogGE{
    namespace Database{
        DatabaseErrorException::DatabaseErrorException(std::string reason){
            this->mMessage = "Database Error: ";
            this->mMessage += reason;
        }
        const char* DatabaseErrorException::what() const throw(){
            return this->mMessage.c_str();
        }
    }
}