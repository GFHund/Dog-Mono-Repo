#include <Exceptions/NothingRecivedException.h>

namespace DogGE{
    namespace Network{
        const char* NothingRecivedException::what() const throw(){
            return "Nothing Recived";
        }
    }
}