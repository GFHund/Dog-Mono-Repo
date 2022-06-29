#ifndef __ABSTRACT_SERVER__
#define __ABSTRACT_SERVER__
#pragma once

#include <AbstractNetwork.h>
#include <ClientConnection.h>

namespace DogGE{
    namespace Network{
        class AbstractServer:public AbstractNetwork{
            protected:
            void initServer(NetworkType type,IP_Type ipType,std::string port);
            public:
            void listenNetwork();
            virtual ClientConnection acceptConnection();
        };
    }
}

#endif