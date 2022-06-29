#ifndef __TCP_CLIENT__
#define __TCP_CLIENT__

#include <AbstractClient.h>

namespace DogGE{
    namespace Network{
        class TcpClient:public AbstractClient{
            public:
            void init(std::string addr,std::string port);
        };
    }
}

#endif