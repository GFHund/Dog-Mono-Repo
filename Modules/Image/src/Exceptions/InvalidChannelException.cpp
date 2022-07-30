#include <Exceptions/InvalidChannelException.h>
namespace DogGE{
    namespace Image{
        InvalidChannelException::InvalidChannelException(int channel){
            this->mChannel = channel;
            this->mMessage = "Error: Invalid Channel: Given Channel ";
            this->mMessage += std::to_string(channel);
        }
        const char* InvalidChannelException::what() const throw(){
            return this->mMessage.c_str();
        }
    }
}