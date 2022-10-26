#include <ConvertOptionsCommand.h>

namespace DogGE{
    namespace TelemetryWsServer{
        ConvertOptionsCommand::ConvertOptionsCommand(){}
        AbstractCommand::COMMAND_TYPE ConvertOptionsCommand::getCommandType(){
            return COMMAND_TYPE::GET_CONVERT_OPTIONS;
        }
        void ConvertOptionsCommand::setFile1(std::string file1){
            this->file1 = file1;
        }
        std::string ConvertOptionsCommand::getFile1(){
            return this->file1;
        }
    }
}