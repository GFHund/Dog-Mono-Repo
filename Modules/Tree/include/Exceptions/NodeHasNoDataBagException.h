#ifndef __NodeHasNoDataBagException__
#define __NodeHasNoDataBagException__

#include <exception>

namespace DogGE{
    namespace Tree{
        class NodeHasNoDataBagException:public std::exception{
            virtual const char* what() const throw();
        };
    }
}
#endif