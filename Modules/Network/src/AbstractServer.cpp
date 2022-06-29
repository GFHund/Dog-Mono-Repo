#include <AbstractServer.h>
#include <Exceptions/NetworkException.h>

namespace DogGE{
    namespace Network{
        void AbstractServer::initServer(NetworkType type,IP_Type ipType,std::string port){
            
            this->setAddrInfo(type,ipType);
            hints.ai_flags = AI_PASSIVE;
            this->addrTranslation("",port);
            this->initSocket();
            int iResult = bind(mSocket,result->ai_addr,(int)result->ai_addrlen);
            if(iResult == SOCKET_ERROR){
                //printf("bind failed with error: %d\n", WSAGetLastError());
                int errorCode = WSAGetLastError();
                freeaddrinfo(result);
                closesocket(mSocket);
                WSACleanup();
                //return 1;
                throw NetworkException(errorCode);
            }
            freeaddrinfo(result);
        }

        void AbstractServer::listenNetwork(){
            if(listen(mSocket,SOMAXCONN) == SOCKET_ERROR){
                //printf( "Listen failed with error: %ld\n", WSAGetLastError() );
                int errorCode = WSAGetLastError();
                closesocket(mSocket);
                WSACleanup();
                //return 1;
                throw NetworkException(errorCode);
            }
        }
        ClientConnection AbstractServer::acceptConnection(){
            SOCKET clientSocket = INVALID_SOCKET;
            clientSocket = accept(mSocket,NULL,NULL);
            if(clientSocket == INVALID_SOCKET){
                //printf("accept failed: %d\n", WSAGetLastError());
                int errorCode = WSAGetLastError();
                closesocket(mSocket);
                WSACleanup();
                //return 1;
                throw NetworkException(errorCode);
            }
            return ClientConnection(clientSocket);
        }
    }
}