using System;
using System.Net.Sockets;
using StateMachineCs;
using System.Collections.Generic;

namespace TelemetryWsServerCs{
    class TelemetryWebSocketConnection: AbstractWebSocketConnection{
        public TelemetryWebSocketConnection(TcpClient client)
        :base(client){}

        protected override void reciveMessage(byte[] incomingByte){
            /*
            Console.WriteLine("Recived Bytes:");
            for(int i=0;i<incomingByte.Length;i++){
                Console.WriteLine(incomingByte[i]);
            }
            */
            string commandString = this.convertIncomingMessageToString(incomingByte);
            Console.WriteLine("Recived:"+commandString);
            //this.sendString("Hallo Welt",true);

            StateMachine<char> sm = new StateMachine<char>();
            
            uint startState = sm.addState();
            uint openState = sm.addState();
            uint drawDiagramState = sm.addState();
            uint getPointsState = sm.addState();

            uint convertState = sm.addState();
            uint convertFile1State = sm.addState();
            uint convertFileIntoState = sm.addState();
            uint convertFile2State = sm.addState();
            uint convertKeyWordUsingState = sm.addState();
            uint convertConvertOptionState = sm.addState();

            uint convertOptionsState = sm.addState();
            uint convertOptionsFile1State = sm.addState();
            //uint quitState = sm.addState();
            uint closeFileState = sm.addState();
            uint cState = sm.addState();
            uint endState = sm.addState();
            Console.WriteLine("EndStateId:"+endState);
            
            
            /*
            OPEN [file];
            CONVERT [file1] INTO [file2] USING [converter] WITH [converter config FILE | (config=>value,...)];
            CONVERT OPTIONS [file1];
            DRAW DIAGRAM WITH x=[xproperty] AND y=[yproperty[|color],...] WHERE
            GET POINTS WITH x=[xproperty] AND y=[yproperty[|color],...] WHERE
            CLOSE [file]
            */
            List<char> buffer = new List<char>();
            AbstractCommand command = new NotInitializedCommand();
            
            sm.addTransition(startState,openState,c => {return c == 'o' || c== 'O';},c => {buffer.Add(c);});
            sm.addTransition(startState,drawDiagramState,c => {return c == 'd' || c== 'D';},c => {buffer.Add(c);});
            sm.addTransition(startState,getPointsState,c => {return c == 'G' || c== 'G';},c => {buffer.Add(c);});
            sm.addTransition(startState,cState,c => {return c == 'c' || c== 'C';},c => {buffer.Add(c);});

            sm.addTransition(cState,convertState,c => {return c == 'o' || c== 'O';},c => {buffer.Add(c);});
            sm.addTransition(convertState,convertState,c => {
                char lastChar = buffer[buffer.Count-1];
                Console.WriteLine("LastChar:"+lastChar);
                if(lastChar == 'o' || lastChar == 'O') return c == 'n' || c == 'N';
                else if(lastChar == 'n' || lastChar == 'N') return c == 'v' || c == 'V';
                else if(lastChar == 'v' || lastChar == 'V') return c == 'e' || c == 'E';
                else if(lastChar == 'e' || lastChar == 'E') return c == 'r' || c == 'R';
                else if(lastChar == 'r' || lastChar == 'R') return c == 't' || c == 'T';
                return false;
            },c => {buffer.Add(c);});
            sm.addTransition(convertState,convertOptionsState,c => {return c == ' ';},c => {buffer.Clear();});
            sm.addTransition(convertOptionsState,convertOptionsState,c => {
                switch(buffer.Count){
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
                }
                return false;
            },c => {buffer.Add(c);});
            sm.addTransition(convertOptionsState,convertOptionsFile1State,c =>{return c == ' ' ;},c=>{command=new ConvertOptionsCommand();buffer.Clear();});
            sm.addTransition(convertOptionsFile1State,convertOptionsFile1State,c =>{return 
            (c >= 'a' && c <= 'z') || 
            (c >= 'A' && c <= 'Z') ||
            (c >= '0' && c <= '9') || 
            (c == '.') || 
            (c == '\\') || 
            (c == ':') || 
            (c=='/');},c=>{buffer.Add(c);});
            sm.addTransition(convertOptionsFile1State,endState,c=>{return c == ';';},c=>{(command as ConvertOptionsCommand).file1 = new string(buffer.ToArray());});
            sm.addTransition(convertOptionsState,convertFile1State,c => {
                if(c == ' ') return false;
                switch(buffer.Count){
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
            },c => {command = new ConvertCommand();buffer.Add(c);});



            sm.addTransition(convertFile1State,convertFile1State,c => {return 
            (c >= 'a' && c <= 'z') || 
            (c >= 'A' && c <= 'Z') || 
            (c == '.') || 
            (c == '\\') || 
            (c == ':') || 
            (c=='/');},c => {buffer.Add(c);});
            sm.addTransition(convertFile1State,convertFileIntoState,c => {return c == ' ';},c => {(command as ConvertCommand).file1 = new string(buffer.ToArray());buffer.Clear();});
            sm.addTransition(convertFileIntoState,convertFileIntoState,c => {
                switch(buffer.Count){
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
            },c => {buffer.Add(c);});
            sm.addTransition(convertFileIntoState,convertFile2State,c => {return c == ' ';},c => {buffer.Clear();});
            sm.addTransition(convertFile2State,convertFile2State,c => {return 
            (c >= 'a' && c <= 'z') || 
            (c >= 'A' && c <= 'Z') || 
            (c == '.') || 
            (c == '\\') || 
            (c == ':') || 
            (c=='/');},c => {buffer.Add(c);});
            sm.addTransition(convertFile2State,endState,c=>{return c == ';';},c => {(command as ConvertCommand).file2 = new string(buffer.ToArray());buffer.Clear();});
            sm.addTransition(convertFile2State,convertKeyWordUsingState,c => {return c == ' ';},c =>{(command as ConvertCommand).file2 = new string(buffer.ToArray());buffer.Clear();});
            sm.addTransition(convertKeyWordUsingState,convertKeyWordUsingState,c => {
                switch(buffer.Count){//USING
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
            },c => buffer.Add(c));
            sm.addTransition(convertKeyWordUsingState,convertConvertOptionState, c => {return c == ' ';},c => {buffer.Clear();});
            sm.addTransition(convertConvertOptionState,convertConvertOptionState,c=> {return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');},c => {buffer.Add(c);});
            sm.addTransition(convertConvertOptionState,endState,c => {return c == ';';},c => {(command as ConvertCommand).convertMethod = new string(buffer.ToArray());buffer.Clear();});

            sm.addTransition(cState,closeFileState,c => {return c == 'l' || c== 'L';},c => {});
            
            //sm.addTransition(startState,convertState,c => {return c == 'c' || c== 'C';},c => {});
            char[] commandChars = commandString.ToCharArray();
            //sm.getState(2);
            //sm.getCurrentStateData();
            for(int i = 0;i < commandChars.Length;i++){
                try{
                    Console.WriteLine("i:" + i);
                    Console.WriteLine("CurrentStateBefore:"+sm.getCurrentStateId());
                    sm.transition(commandChars[i]);//commandChars[i]
                    Console.WriteLine("CurrentStateAfter:"+sm.getCurrentStateId());
                } catch(TransitionNotFoundException<char> e){
                    //Console.WriteLine("Error:"+ e.ToString());
                    Console.WriteLine("Error:"+ e.GetMessage());
                    return;
                } catch(Exception e){
                    Console.WriteLine("Error:"+ e.ToString());
                    return;
                }
            }
            if(command is ConvertCommand){
                F1_2022_Ct_Converter converter = new F1_2022_Ct_Converter();
                if(converter.canConvert((command as ConvertCommand).file1)){
                    converter.convert((command as ConvertCommand).file1,(command as ConvertCommand).file2);
                }
            } else if(command is ConvertOptionsCommand){
                string list = "{\"type\":\"convertOptions\",\"data\":[\"F1_2022_cf\"]}";
                this.sendString(list);
            }
        }
    }
}