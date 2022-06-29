#ifndef __CLIENT_CONNECTION__
#define __CLIENT_CONNECTION__
#pragma once

#include <WinSock2.h>
#include <windows.h>
#include <ws2tcpip.h>

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
    }
}


#endif