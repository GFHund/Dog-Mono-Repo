#include <ClientConnection.h>
#include <Exceptions/NetworkException.h>

namespace DogGE{
    namespace Network{
        ClientConnection::ClientConnection(SOCKET socket){
            this->mSocket = socket;
        }
        template <size_t N>
        void ClientConnection::sendData(std::array<char,N> data){
            int iResult = send(this->mSocket,data.data(),data.size(),0);
            if (iSendResult == SOCKET_ERROR) {
                //printf("send failed: %d\n", WSAGetLastError());
                int errorCode = WSAGetLastError();
                closesocket(ClientSocket);
                WSACleanup();
                throw NetworkExceptions(errorCode);
            }
            
        }
        template <size_t N>
        std::array<char,N> ClientConnection::recvData(){
            std::array<char,N> ret;
            int iResult = recv(this->mSocket,ret.data(),ret.size(),0);
            if (iSendResult == SOCKET_ERROR) {
                //printf("send failed: %d\n", WSAGetLastError());
                int errorCode = WSAGetLastError();
                closesocket(ClientSocket);
                WSACleanup();
                throw NetworkExceptions(errorCode);
            }
            return ret;
        }
    }
}