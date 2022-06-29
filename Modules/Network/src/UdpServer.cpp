#include <UdpServer.h>
namespace DogGE{
    namespace Network{
        void UdpServer::init(std::string port){
            initServer(NetworkType::NETWORK_UDP,IP_Type::IP_TYPE_V4,port);
        }
    }
}