#include <Exceptions/NodeHasNoDataBagException.h>

namespace DogGE{
    namespace Tree{
        const char* NodeHasNoDataBagException::what() const throw(){
            return "Node has no Data Bag";
        }
    }
}
