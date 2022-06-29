#include <Exceptions/PackageNotFoundException.h>

namespace DogGE{
    namespace F1GameParserGenerator{
        PackageNotFoundException::PackageNotFoundException(std::string packageName){
            this->mPackageName = packageName;
            this->mMessage = "Package not found Exception: "+packageName;
        }
        const char* PackageNotFoundException::what() const throw(){
            return mMessage.c_str();
        }
    }
}