#include <Exceptions/DataTypeNotFoundException.h>

namespace DogGE{
    namespace F1GameParserGenerator{
        DataTypeNotFoundException::DataTypeNotFoundException(std::string dataType,int size){
            this->mDataType = dataType;
            this->mDataTypeSize = size;
            this->mMessage = "Data Type not found Exception: "+dataType+" ("+std::to_string(size)+")";
        }
        const char* DataTypeNotFoundException::what() const throw(){
            return mMessage.c_str();
        }
    }
}