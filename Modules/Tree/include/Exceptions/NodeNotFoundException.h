#ifndef __ROOT_NOT_FOUND_EXCEPTION__
#define __ROOT_NOT_FOUND_EXCEPTION__

#include <exception>

namespace DogGE{
    namespace Tree{
        class NodeNotFoundException:public std::exception{
            public:
            virtual const char* what() const throw();
        };
    }
}

#endif