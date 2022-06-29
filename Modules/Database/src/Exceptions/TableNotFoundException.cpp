#include <Exceptions/TableNotFoundException.h>

namespace DogGE{
    namespace Database{
        TableNotFoundException::TableNotFoundException(std::string tablename){
            this->mTableName = tablename;
            this->mMessage = "Error: Could not find Table ";
            this->mMessage += tablename;
        }
        const char* TableNotFoundException::what() const throw(){
            return this->mMessage.c_str();
        }
    }
}