#include <Exceptions/NodeNotFoundException.h>

namespace DogGE{
    namespace Tree{
        const char* NodeNotFoundException::what() const throw(){
            return "Node not found";
        }
    }
}