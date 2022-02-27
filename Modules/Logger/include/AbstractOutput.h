#ifndef __ABSTRACT_OUTPUT__
#define __ABSTRACT_OUTPUT__

#include <string>

namespace DogGE{
    namespace Logger{
        class AbstractOutput{
            public:
            virtual void output(std::string message) = 0;
        };
    }
}

#endif