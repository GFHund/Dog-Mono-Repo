#include <iostream>
#include <windows.h>
#include <WsServer.h>
#include <WsClientConnection.h>
#include <CommandParser.h>
#include <ConvertOptionsCommand.h>
#include <thread>
#include <vector>
#include <cstring>
#include <string>

bool bCloseProgram;

BOOL WINAPI CtrlHandler(DWORD fdwCtrlType){
    
    if(fdwCtrlType == CTRL_C_EVENT){
        std::cout << "Exit Program" << std::endl;
        bCloseProgram = true;
        return true;
    }
    return false;
}

void acceptConnection(DogGE::Network::WsClientConnection* conn){
    do{
        std::cout << "wait for incoming Messeges" << std::endl;
        std::array<char,2000> recv = conn->recvData<2000>();
        std::cout << "recived incoming Message" << std::endl;
        if(conn->isString<2000>(recv)){
            std::cout << "Messege is string" << std::endl;
            std::string messageString = conn->getString<2000>(recv);
            std::cout << messageString << std::endl;
            DogGE::TelemetryWsServer::CommandParser parser;
            std::array<char,2000> arrString;
            std::memcpy(arrString.data(),messageString.c_str(),messageString.size());
            DogGE::TelemetryWsServer::AbstractCommand* command = parser.parse(arrString);
            if(command->getCommandType() == DogGE::TelemetryWsServer::AbstractCommand::GET_CONVERT_OPTIONS){
                std::string list = "{\"type\":\"convertOptions\",\"data\":[\"F1_2022_cf\"]}";
                DogGE::TelemetryWsServer::ConvertOptionsCommand* convertOptionsCommand = (DogGE::TelemetryWsServer::ConvertOptionsCommand*)command;
                std::array<char,2000> responseRawData = conn->toWebsocketMessage<2000>(list);
                conn->sendData<2000>(responseRawData);
            }
            delete command;
        } else {
            if(recv[0]>0){
                std::cout << "Messege is NOT string" << std::endl;
                std::cout << std::hex << int(recv[0]) << std::endl;
                std::cout << std::hex << int(recv[1]) << std::endl;
            }
            
        }
    } while(!bCloseProgram);
    std::cout << "delete Connection" << std::endl;
    delete conn;
}

int main(){
    bCloseProgram = false;
    if(!SetConsoleCtrlHandler(CtrlHandler,TRUE)){
        std::cout << "Could not create ctrl handle function" << std::endl;
        return 1;
    }
    DogGE::Network::WsServer server;
    server.init("8080");
    std::vector<std::thread> threads;
    while(!bCloseProgram){
        //std::cout << "listenNetwork" << std::endl;
        server.listenNetwork();
        //std::cout << "acceptConnection" << std::endl;
        DogGE::Network::WsClientConnection* conn = (DogGE::Network::WsClientConnection*) server.acceptConnection();
        if(conn == nullptr){
            continue;
        }
        std::cout << "start Thread" << std::endl;
        threads.push_back(std::thread(acceptConnection,conn));
        /*
        do{
            std::array<char,2000> recv = conn->recvData<2000>();
            if(conn->isString<2000>(recv)){
                std::string messageString = conn->getString<2000>(recv);
                DogGE::TelemetryWsServer::CommandParser parser;
                std::array<char,2000> arrString;
                std::memcpy(arrString.data(),messageString.c_str(),messageString.size());
                DogGE::TelemetryWsServer::AbstractCommand* command = parser.parse(arrString);
                if(command->getCommandType() == DogGE::TelemetryWsServer::AbstractCommand::GET_CONVERT_OPTIONS){
                    std::string list = "{\"type\":\"convertOptions\",\"data\":[\"F1_2022_cf\"]}";
                    DogGE::TelemetryWsServer::ConvertOptionsCommand* convertOptionsCommand = (DogGE::TelemetryWsServer::ConvertOptionsCommand*)command;
                    std::array<char,2000> responseRawData = conn->toWebsocketMessage<2000>(list);
                    conn->sendData<2000>(responseRawData);
                }
                delete command;
            }
        } while(!bCloseProgram);
        */
        delete conn;
    }
    return 0;
}