#include <CommandParser.h>
#include <StateMachine.h>

namespace DogGE{
    namespace TelemetryWsServer{
        AbstractCommand* CommandParser::parse(std::array<char,2000> string){
            DogGE::StateMachine::StateMachine<char> sm;
            int startState = sm.addState();
            int openState = sm.addState();
            int drawDiagramState = sm.addState();
            int getPointsState = sm.addState();
            int convertState = sm.addState();
            int getConvertOptionsState = sm.addState();
            int quitState = sm.addState();
            int closeFileState = sm.addState();

            sm.addTransition(startState,openState,[]())
        }
    }
}