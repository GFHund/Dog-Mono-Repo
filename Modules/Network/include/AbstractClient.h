#ifndef __ABSTRACT_CLIENT__
#define __ABSTRACT_CLIENT__
#pragma once

#include <AbstractNetwork.h>
#include <Exceptions/NetworkException.h>
#include <Exceptions/NothingRecivedException.h>

namespace DogGE{
    namespace Network{
        class AbstractClient:public AbstractNetwork{
            protected:
            void initClient(NetworkType type,IP_Type ipType,std::string addr,std::string port);
            NetworkType mNetworkType;

            public:
            template<size_t N>
            void sendData(std::array<char,N> data);
            template<size_t N>
            std::array<char,N> recvData();
        };

        template<size_t N>
        std::array<char,N> AbstractClient::recvData(){
            std::array<char,N> ret;
            int iResult = 0;
            SOCKADDR_IN remoteAddr;
            int remoteAddrSize = sizeof(remoteAddr);
            if(this->mNetworkType == NETWORK_TCP){
                iResult = recv(this->mSocket,ret.data(),ret.size(),0);
            } else {
                iResult = recvfrom(this->mSocket,ret.data(),ret.size(),0,(SOCKADDR*)&remoteAddr,&remoteAddrSize);
            }
            
            if (iResult == SOCKET_ERROR) {
                //printf("send failed: %d\n", WSAGetLastError());
                int errorCode = WSAGetLastError();
                //If timeout error occur than do nothing. The Caller of the method should handle this situation
                if(errorCode != 10060){
                    closesocket(this->mSocket);
                    WSACleanup();
                    throw NetworkException(errorCode);
                }
                throw NothingRecivedException();
            }
            if(iResult > 0){
                return ret;
            }
            throw NothingRecivedException();
        }
    }
}

#endif