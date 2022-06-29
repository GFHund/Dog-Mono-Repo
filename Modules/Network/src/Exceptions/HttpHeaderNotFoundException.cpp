#include <Exceptions/HttpHeaderNotFoundException.h>

namespace DogGE{
    namespace Network{
        HttpHeaderNotFoundException::HttpHeaderNotFoundException(std::string headerName){
            this->mHeaderName = headerName;
            this->mMessage = "Error: Couldn't find Header: "+headerName;
        }
        const char* HttpHeaderNotFoundException::what() const throw(){
            return this->mMessage.c_str();
        }
    }
}