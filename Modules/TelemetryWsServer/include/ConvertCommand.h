#ifndef __CONVERT_COMMAND__
#define __CONVERT_COMMAND__
#pragma once

#include <string>
#include <AbstractCommand.h> 

namespace DogGE{
    namespace TelemetryWsServer{
        class ConvertCommand: public AbstractCommand{
            protected:
            std::string file1;
            std::string file2;
            std::string convertMethod;
            std::string convertConfig;
            public:
            ConvertCommand();
            AbstractCommand::COMMAND_TYPE getCommandType() override;
            void setFile1(std::string file1);
            void setFile2(std::string file2);
            void setConvertMethod(std::string convertMethod);
            void setConvertConfig(std::string convertConfig);
            std::string getFile1();
            std::string getFile2();
            std::string getConvertMethod();
            std::string getConvertConfig();

        };
    }
}

#endif