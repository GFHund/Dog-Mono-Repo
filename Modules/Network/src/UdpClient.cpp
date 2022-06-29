#include <UdpClient.h>

namespace DogGE{
    namespace Network{
        void UdpClient::init(std::string addr,std::string port){
            initClient(NetworkType::NETWORK_UDP,IP_Type::IP_TYPE_V4,addr,port);
        }
    }
}