#ifndef __COMMAND_PARSER__
#define __COMMAND_PARSER__

#include <AbstractCommand.h>
#include <array>
namespace DogGE{
    namespace TelemetryWsServer{
        class CommandParser{
            AbstractCommand* parse(std::array<char,2000> string);
        };
    }
}
#endif