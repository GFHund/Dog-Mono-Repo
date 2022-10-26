#ifndef __ABSTRACT_NETWORK__
#define __ABSTRACT_NETWORK__
#pragma once

#include <WinSock2.h>

#include <ws2tcpip.h>
#include <string>

#include <array>

namespace DogGE{
    namespace Network{
        class AbstractNetwork{
            protected:
            struct addrinfo *result = NULL,*ptr = NULL,hints;
            SOCKET mSocket;
            enum NetworkType{
                NETWORK_TCP,
                NETWORK_UDP
            };
            enum Role{
                ROLE_SERVER,
                ROLE_CLIENT
            };
            enum IP_Type{
                IP_TYPE_V4,
                IP_TYPE_V6,
                IP_TYPE_BOTH
            };
            void setAddrInfo(NetworkType type,IP_Type ipType);
            void addrTranslation(std::string addr,std::string port);
            void initSocket();
            public:
            AbstractNetwork();
            ~AbstractNetwork();
            void close();
        };
    }
}

#endif