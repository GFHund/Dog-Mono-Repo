#include <Exceptions/OutOfBoundsException.h>
#include <string>
#include <cstring>
namespace DogGE{
    namespace Math{
        OutOfBoundsException::OutOfBoundsException(int maxAllowedValue,int givenValue){
            this->mMaxAllowedValue = maxAllowedValue;
            this->mGivenValue = givenValue;
        }
        const char* OutOfBoundsException::what() const throw(){
            std::string message = "Out of Bound Exception - Max Allowed Value: ";
            message += std::to_string(this->mMaxAllowedValue);
            message += " - Given Value: ";
            message += std::to_string(this->mGivenValue);
            char* ret = new char[message.size()];
            strcpy(ret,message.c_str());
            return ret;//ret.c_str();
        }
    }
}