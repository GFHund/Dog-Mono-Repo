#ifndef __WS_CLIENT__
#define __WS_CLIENT__

#include <TcpClient.h>

namespace DogGE{
    namespace Network{
        class WsClient: public TcpClient{
            void performHandshake();
        }
    }
}
#endif