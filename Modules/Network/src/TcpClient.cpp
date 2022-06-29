#include <TcpClient.h>

namespace DogGE{
    namespace Network{
        void TcpClient::init(std::string addr,std::string port){
            initClient(NetworkType::NETWORK_TCP,IP_Type::IP_TYPE_V4,addr,port);
        }
    }
}