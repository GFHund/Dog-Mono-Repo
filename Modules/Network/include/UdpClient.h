#ifndef __UDP_CLIENT__
#define __UDP_CLIENT__
#pragma once

#include <AbstractClient.h>

namespace DogGE{
    namespace Network{
        class UdpClient:public AbstractClient{
            protected:
            
            public:
            void init(std::string addr,std::string port);
        };
    }
}

#endif