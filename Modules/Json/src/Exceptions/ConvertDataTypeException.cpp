#include <Exceptions/ConvertDataTypeException.h>

namespace DogGE{
    namespace Json{
        ConvertDataTypeException::ConvertDataTypeException(std::string fromType,std::string toType){
            mFromType = fromType;
            mToType = toType;
            mMessage = "Error at convert from Type ";
            mMessage += fromType;
            mMessage += " to Type ";
            mMessage += toType;
        }
        const char* ConvertDataTypeException::what() const throw(){
            return mMessage.c_str();
        }
    }
}

