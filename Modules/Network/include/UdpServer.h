#ifndef __UDP_SERVER__
#define __UDP_SERVER__
#pragma once

#include <AbstractServer.h>

namespace DogGE{
    namespace Network{
        class UdpServer:public AbstractServer{
            public:
            void init(std::string port);
        };
    }
}
#endif