#include <CommandParser.h>
#include <StateMachine.h>
#include <Exceptions\TransitionNotFoundException.h>
#include <ConvertOptionsCommand.h>
#include <ConvertCommand.h>
#include <iostream>

namespace DogGE{
    namespace TelemetryWsServer{
        AbstractCommand* CommandParser::parse(std::array<char,2000> commandString){
            DogGE::StateMachine::StateMachine<char> sm;
            AbstractCommand* command;

            int startState = sm.addState();
            int openState = sm.addState();
            int drawDiagramState = sm.addState();
            int getPointsState = sm.addState();
            
            int convertState = sm.addState();
            int convertFile1State = sm.addState();
            int convertFileIntoState = sm.addState();
            int convertFile2State = sm.addState();
            int convertKeyWordUsingState = sm.addState();
            int convertConvertOptionState = sm.addState();

            int convertOptionsState = sm.addState();
            int convertOptionsFile1State = sm.addState();

            int closeFileState = sm.addState();
            int cState = sm.addState();
            int endState = sm.addState();
            
            std::string buffer;

            sm.addTransition(startState,openState,[](char c)->bool{
                return c == 'o' || c== 'O';
            },[&](char i){buffer += i;});
            sm.addTransition(startState,drawDiagramState,[](char c)->bool{
                return c == 'd' || c== 'D';
            },[&](char i){buffer += i;});
            sm.addTransition(startState,getPointsState,[](char c)->bool{
                return c == 'G' || c== 'G';
            },[&](char i){buffer += i;});
            sm.addTransition(startState,cState,[](char c)->bool{
                return c == 'c' || c== 'C';
            },[&](char i){buffer += i;});
        
            sm.addTransition(cState,convertState,[](char c)->bool{
                return c == 'o' || c== 'O';
            },[&](char i){buffer += i;});
            sm.addTransition(convertState,convertState,[&](char c)->bool{
                int length = buffer.length();
                switch(length){
                    case 2:
                        return c == 'n' || c == 'N';
                    case 3:
                        return c == 'v' || c == 'V';
                    case 4:
                        return c == 'e' || c == 'E';
                    case 5:
                        return c == 'r' || c == 'R';
                    case 6:
                        return c == 't' || c == 'T';
                    default:
                        return false;
                }
            },[&](char i){buffer += i;});
            sm.addTransition(convertState,convertOptionsState,[](char c)->bool{return c==' ';},[&](char i){buffer.clear();});
            sm.addTransition(convertOptionsState,convertOptionsState,[&](char c)->bool{
                switch(buffer.length()){
                    case 0:
                        return c == 'O' || c == 'o';
                    case 1:
                        return c == 'P' || c == 'p';
                    case 2:
                        return c == 'T' || c == 't';
                    case 3:
                        return c == 'I' || c == 'i';
                    case 4:
                        return c == 'O' || c == 'o';
                    case 5:
                        return c == 'N' || c == 'n';
                    case 6:
                        return c == 'S' || c == 's';
                    default:
                        return false;
                }
            },[&](char c){buffer += c;});
            sm.addTransition(convertOptionsState,convertOptionsFile1State,[](char c)->bool{return c == ' ';},[&](char c){command = new ConvertOptionsCommand();buffer.clear();});
            sm.addTransition(convertOptionsFile1State,convertOptionsFile1State,[](char c)->bool{
                return (c >= 'a' && c <= 'z') || 
                (c >= 'A' && c <= 'Z') ||
                (c >= '0' && c <= '9') || 
                (c == '.') || 
                (c == '\\') || 
                (c == ':') || 
                (c=='/');
            },[&](char c){buffer += c;});
            sm.addTransition(convertOptionsFile1State,endState,[](char c)->bool{return c == ';';},[&](char c){((ConvertOptionsCommand*)command)->setFile1(buffer);});
            sm.addTransition(convertOptionsState,convertFile1State,[&](char c)->bool{
                if(c == ' ') return false;
                switch(buffer.length()){
                    case 0:
                        return c != 'O' && c != 'o';
                    case 1:
                        return c != 'P' && c != 'p';
                    case 2:
                        return c != 'T' && c != 't';
                    case 3:
                        return c != 'I' && c != 'i';
                    case 4:
                        return c != 'O' && c != 'o';
                    case 5:
                        return c != 'N' && c != 'n';
                    case 6:
                        return c != 'S' && c != 's';
                }
                return false;
            },[&](char c){command = new ConvertCommand();buffer += c;});
            sm.addTransition(convertFile1State,convertFile1State,[](char c)->bool{
                return (c >= 'a' && c <= 'z') || 
                (c >= 'A' && c <= 'Z') || 
                (c == '.') || 
                (c == '\\') || 
                (c == ':') || 
                (c=='/');
            },[&](char c){buffer += c;});
            sm.addTransition(convertFile1State,convertFileIntoState,[](char c)->bool{return c == ' ';},[&](char c){((ConvertCommand*)command)->setFile1(buffer);buffer.clear();});
            sm.addTransition(convertFileIntoState,convertFileIntoState,[&](char c)->bool{
                switch(buffer.length()){
                    case 0:
                        return c == 'I' || c == 'i';
                    case 1:
                        return c == 'N' || c == 'n';
                    case 2:
                        return c == 'T' || c == 't';
                    case 3:
                        return c == 'O' || c == 'o';
                }
                return false;
            },[&](char c){buffer += c;});
            sm.addTransition(convertFileIntoState,convertFile2State,[](char c)->bool{return c == ' ';},[&](char c){buffer.clear();});
            sm.addTransition(convertFile2State,convertFile2State,[](char c)->bool{
            return (c >= 'a' && c <= 'z') || 
            (c >= 'A' && c <= 'Z') || 
            (c == '.') || 
            (c == '\\') || 
            (c == ':') || 
            (c=='/');
            },[&](char c){buffer+=c;});
            sm.addTransition(convertFile2State,endState,[](char c)->bool{return c == ';';},[&](char c){((ConvertCommand*)command)->setFile2(buffer);buffer.clear();});
            sm.addTransition(convertFile2State,convertKeyWordUsingState,[](char c)->bool{return c == ' ';},[&](char c){((ConvertCommand*)command)->setFile2(buffer);buffer.clear();});
            sm.addTransition(convertKeyWordUsingState,convertKeyWordUsingState,[&](char c)->bool{
                switch(buffer.length()){//USING
                    case 0:
                        return c == 'U' || c == 'u';
                    case 1:
                        return c == 'S' || c == 's';
                    case 2:
                        return c == 'I' || c == 'i';
                    case 3:
                        return c == 'N' || c == 'n';
                    case 4:
                        return c == 'G' || c == 'g';
                }
                return false;
            },[&](char c){buffer += c;});
            sm.addTransition(convertKeyWordUsingState,convertConvertOptionState,[](char c)->bool{return c == ' ';},[&](char c){buffer.clear();});
            sm.addTransition(convertConvertOptionState,convertConvertOptionState,[](char c)->bool{return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');},[&](char c){buffer += c;});
            sm.addTransition(convertConvertOptionState,endState,[](char c)->bool{return c == ';';},[&](char c){((ConvertCommand*)command)->setConvertMethod(buffer);buffer.clear();});
            sm.addTransition(cState,closeFileState,[](char c)->bool{return c == 'l' || c == 'L';},[&](char c){});
            for(int i=0; i< commandString.size();i++){
                try{
                    sm.transition(commandString[i]);
                } catch(DogGE::StateMachine::TransitionNotFoundException<char> &e){
                    std::cout << e.what() << std::endl;
                } catch(std::exception &e){
                    std::cout << e.what() << std::endl;
                }
            }
            return command;
        }
    }
}