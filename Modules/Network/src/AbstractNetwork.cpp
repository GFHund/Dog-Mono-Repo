#include <AbstractNetwork.h>
#include <Exceptions/NetworkException.h>
namespace DogGE{
    namespace Network{
        void AbstractNetwork::setAddrInfo(NetworkType type,IP_Type ipType){
            int iResult;
            WSADATA wsaData;
            iResult = WSAStartup(MAKEWORD(2,2),&wsaData);
            if(iResult != 0){
                //std::cout << "WSA Startup Failed: " << iResult << std::endl;
                return;
            }

            ZeroMemory(&hints,sizeof(hints));
            if(ipType == IP_TYPE_V4){
                hints.ai_family = AF_INET;
            } else if(ipType == IP_TYPE_V6){
                hints.ai_family = AF_INET6;
            } else {
                hints.ai_family = AF_UNSPEC;
            }
            
            if(type == NETWORK_UDP){
                hints.ai_socktype = SOCK_DGRAM;
                hints.ai_protocol = IPPROTO_UDP;
            } else {
                hints.ai_socktype = SOCK_STREAM;
                hints.ai_protocol = IPPROTO_TCP;
            }
            
        
        }

        void AbstractNetwork::addrTranslation(std::string addr,std::string port){
            int iResult;
            if(addr.size() == 0){
                iResult = getaddrinfo(NULL,port.c_str(),&hints,&result);
            } else {
                iResult = getaddrinfo(addr.c_str(),port.c_str(),&hints,&result);
            }
            
            if(iResult != 0){
                WSACleanup();
                throw NetworkException(iResult);
            }
        }
        void AbstractNetwork::initSocket(){
            mSocket = INVALID_SOCKET;
            //oSocket = socket(hints.ai_family,hints.ai_socktype,hints.ai_protocol);
            mSocket = socket(result->ai_family,result->ai_socktype,result->ai_protocol);
            if(mSocket == INVALID_SOCKET){
                //printf("Error at socket(): %ld\n", WSAGetLastError());
                int errorCode = WSAGetLastError();
                freeaddrinfo(result);
                WSACleanup();
                //return 1;
                throw NetworkException(errorCode);
            }
            
        }

        AbstractNetwork::AbstractNetwork(){
            mSocket = INVALID_SOCKET;
        }

        AbstractNetwork::~AbstractNetwork(){
            close();
        }

        void AbstractNetwork::close(){
            int iResult = shutdown(this->mSocket,SD_SEND);
            closesocket(this->mSocket);
            WSACleanup();
        }   
    }
}