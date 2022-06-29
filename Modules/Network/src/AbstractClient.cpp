#include <AbstractClient.h>



namespace DogGE{
    namespace Network{
        void AbstractClient::initClient(NetworkType type,IP_Type ipType,std::string addr,std::string port){
            mNetworkType = type;
            int iPort = std::stoi(port);

            this->setAddrInfo(type,ipType);
            this->addrTranslation(addr,port);
            this->initSocket();

            struct sockaddr_in RecvAddr;
            RecvAddr.sin_family = AF_INET;
            RecvAddr.sin_port = htons(iPort);
            RecvAddr.sin_addr.s_addr = htonl(INADDR_ANY);

            if(type == NetworkType::NETWORK_UDP){
                int iResult = bind(mSocket,(SOCKADDR*)&RecvAddr,sizeof(RecvAddr));
                if(iResult == SOCKET_ERROR){
                    closesocket(mSocket);
                    mSocket = INVALID_SOCKET;
                }
                freeaddrinfo(result);

                if(mSocket == INVALID_SOCKET){
                    //std::cout << "Unable to connect to server!" << std::endl;
                    WSACleanup();
                    return;
                }
                const int buflen = 2000;
                char* recvbuf = new char[buflen];
                SOCKADDR_IN remoteAddr;
                int remoteAddrSize = sizeof(remoteAddr);
            } else {
                int iResult = connect(mSocket,ptr->ai_addr,(int)ptr->ai_addrlen);
                if(iResult == SOCKET_ERROR){
                    closesocket(mSocket);
                    mSocket = INVALID_SOCKET;
                }
                freeaddrinfo(result);
                if(mSocket == INVALID_SOCKET){
                    WSACleanup();
                }
            }
            const int timeout = 1000;
            setsockopt(mSocket,SOL_SOCKET,SO_RCVTIMEO,(const char*)&timeout,sizeof(int));
            
        }

        template<size_t N>
        void AbstractClient::sendData(std::array<char,N> data){
            int iResult = send(this->mSocket,data.data(),data.size(),0);
            if (iResult == SOCKET_ERROR) {
                //printf("send failed: %d\n", WSAGetLastError());
                int errorCode = WSAGetLastError();
                closesocket(this->mSocket);
                WSACleanup();
                throw NetworkException(errorCode);
            }
        }
    }
}