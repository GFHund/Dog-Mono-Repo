#include <iostream>
#include <windows.h>
#include <WsServer.h>
#include <thread>
#include <vector>

bool bCloseProgram;

BOOL WINAPI CtrlHandler(DWORD fdwCtrlType){
    
    if(fdwCtrlType == CTRL_C_EVENT){
        std::cout << "Exit Program" << std::endl;
        bCloseProgram = true;
        return true;
    }
    return false;
}

void acceptConnection(DogGE::Network::ClientConnection conn){
    do{
        std::array<char,2000> recv = conn.recvData<2000>();
        
    } while(bCloseProgram);
}

int main(){
    bCloseProgram = false;
    if(!SetConsoleCtrlHandler(CtrlHandler,TRUE)){
        std::cout << "Could not create ctrl handle function" << std::endl;
        return 1;
    }
    DogGE::Network::WsServer server;
    server.init("6768");
    std::vector<std::thread> threads;
    while(bCloseProgram){
        server.listenNetwork();
        DogGE::Network::ClientConnection conn = server.acceptConnection();
        threads.push_back(std::thread(acceptConnection,conn));
        
    }
    return 0;
}