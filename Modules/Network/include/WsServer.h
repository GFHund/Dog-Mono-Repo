#ifndef __WS_SERVER__
#define __WS_SERVER__
#pragma once

#include <TcpServer.h>

namespace DogGE{
    namespace Network{
        class WsServer:public TcpServer{
            public:
            ClientConnection acceptConnection() override;
        };
    }
}
#endif