#ifndef __CONVERT_OPTIONS_COMMAND__
#define __CONVERT_OPTIONS_COMMAND__

#include <string>
#include <AbstractCommand.h>

namespace DogGE{
    namespace TelemetryWsServer{
        class ConvertOptionsCommand:public AbstractCommand{
            private:
            std::string file1;
            public:
            ConvertOptionsCommand();
            AbstractCommand::COMMAND_TYPE getCommandType() override;
            void setFile1(std::string file1);
            std::string getFile1();
        };
    }
}

#endif