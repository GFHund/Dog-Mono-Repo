#ifndef __FILE_OUTPUT__
#define __FILE_OUTPUT__

#include <AbstractOutput.h>
#include <fstream>

namespace DogGE{
    namespace Logger{
        class FileOutput: public AbstractOutput{
            private:
            std::ofstream mOutput;
            public:
            FileOutput(std::string filename);
            ~FileOutput();
            void output(std::string message) override;
        };
    }
}

#endif