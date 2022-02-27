#include <FileOutput.h>

namespace DogGE{
    namespace Logger{
        FileOutput::FileOutput(std::string filename){
            mOutput = std::ofstream(filename.c_str());
        }
        FileOutput::~FileOutput(){
            mOutput.close();
        }

        void FileOutput::output(std::string message){
            mOutput << message << std::endl;
        }
    }
}