#include <Exceptions/DatabaseNotFoundException.h>

namespace DogGE{
    namespace Database{
        DatabaseNotFoundException::DatabaseNotFoundException(std::string file){
            this->mFile = file;
            this->mMessage = "Error: Could not Open or Create Database File: ";
            this->mMessage += file;
        }
        const char* DatabaseNotFoundException::what() const throw(){
            return this->mMessage.c_str();
        }
    }
}