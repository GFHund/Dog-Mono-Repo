#include <ConvertCommand.h>

namespace DogGE{
    namespace TelemetryWsServer{
        ConvertCommand::ConvertCommand(){}
        AbstractCommand::COMMAND_TYPE ConvertCommand::getCommandType(){
            return COMMAND_TYPE::CONVERT;
        }
        void ConvertCommand::setFile1(std::string file1){
            this->file1 = file1;
        }
        void ConvertCommand::setFile2(std::string file2){
            this->file2 = file2;
        }
        void ConvertCommand::setConvertMethod(std::string convertMethod){
            this->convertMethod = convertMethod;
        }
        void ConvertCommand::setConvertConfig(std::string convertConfig){
            this->convertConfig = convertConfig;
        }
        std::string ConvertCommand::getFile1(){
            return this->file1;
        }
        std::string ConvertCommand::getFile2(){
            return this->file2;
        }
        std::string ConvertCommand::getConvertMethod(){
            return this->convertMethod;
        }
        std::string ConvertCommand::getConvertConfig(){
            return this->convertConfig;
        }
    }
}