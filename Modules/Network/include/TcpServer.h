#ifndef __TCP_SERVER__
#define __TCP_SERVER__
#pragma once


#include <AbstractServer.h>

namespace DogGE{
    namespace Network{
        class TcpServer:public AbstractServer{
            public:
            void init(std::string port);
        };
    } 
}

#endif