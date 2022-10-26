#ifndef __CLIENT_CONNECTION__
#define __CLIENT_CONNECTION__
#pragma once

#include <WinSock2.h>
//#include <windows.h>
#include <ws2tcpip.h>
#include <array>
#include <Exceptions/NetworkException.h>

namespace DogGE{
    namespace Network{
        class ClientConnection{
            private:
            SOCKET mSocket;
            public:
            ClientConnection(SOCKET socket);
            template <size_t N>
            void sendData(std::array<char,N> data);
            template <size_t N>
            std::array<char,N> recvData();
        };

        template <size_t N>
        void ClientConnection::sendData(std::array<char,N> data){
            int iResult = send(this->mSocket,data.data(),data.size(),0);
            if (iResult == SOCKET_ERROR) {
                //printf("send failed: %d\n", WSAGetLastError());
                int errorCode = WSAGetLastError();
                closesocket(mSocket);
                WSACleanup();
                throw NetworkException(errorCode);
            }
            
        }

        template <size_t N>
        std::array<char,N> ClientConnection::recvData(){
            std::array<char,N> ret;
            int iResult = recv(this->mSocket,ret.data(),ret.size(),0);
            if (iResult == SOCKET_ERROR) {
                //printf("send failed: %d\n", WSAGetLastError());
                int errorCode = WSAGetLastError();
                closesocket(mSocket);
                WSACleanup();
                throw NetworkException(errorCode);
            }
            return ret;
        }
    }
}


#endif