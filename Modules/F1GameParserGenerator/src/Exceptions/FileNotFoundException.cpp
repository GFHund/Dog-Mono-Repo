#include <Exceptions/FileNotFoundException.h>

namespace DogGE{
    namespace F1GameParserGenerator{
        FileNotFoundException::FileNotFoundException(std::string filename){
            this->mFilename = filename;
            this->mMessage = "File not found Exception: "+filename;
        }
        const char* FileNotFoundException::what() const throw(){
            return mMessage.c_str();
        }
    }
}