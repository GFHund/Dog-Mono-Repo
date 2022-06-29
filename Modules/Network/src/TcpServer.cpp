#include <TcpServer.h>

namespace DogGE{
    namespace Network{
        void TcpServer::init(std::string port){
            initServer(NetworkType::NETWORK_TCP,IP_Type::IP_TYPE_V4,port);
        }
    }
}