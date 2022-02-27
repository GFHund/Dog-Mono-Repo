#include <ConsoleOutput.h>

#include <iostream>

namespace DogGE{
    namespace Logger{
        void ConsoleOutput::output(std::string message){
            std::cout << message << std::endl;
        }
    }
}