#ifndef __NodeHasNoDataBagException__
#define __NodeHasNoDataBagException__

#include <exception>

namespace DogGE{
    namespace Tree{
        class NodeHasNoDataBagException:public std::exception{
            public:
            virtual const char* what() const throw();
        };
    }
}
#endif