#ifndef __CONSOLE_OUTPUT__
#define __CONSOLE_OUTPUT__

#include <AbstractOutput.h>

namespace DogGE{
    namespace Logger{
        class ConsoleOutput: public AbstractOutput{
            public:
            void output(std::string message) override;
        };
    }
}

#endif