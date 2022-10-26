#include <ClientConnection.h>

namespace DogGE{
    namespace Network{
        ClientConnection::ClientConnection(SOCKET socket){
            this->mSocket = socket;
        }
    }
}