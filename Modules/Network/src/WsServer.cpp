#include <WsServer.h>
#include <HttpRequest.h>
#include <NetworkUtility.h>
#include <Hash.h>

namespace DogGE{
    namespace Network{
        ClientConnection WsServer::acceptConnection(){
            ClientConnection connection = AbstractServer::acceptConnection();
            std::array<char,4096> buffer = connection.recvData<4096>();
            HttpRequest request = HttpRequest::parseRequest(std::string(buffer.data()));
            
            std::string key = request.getHttpHeader("Sec-WebSocket-Key");
            key += "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
            std::string sha1Key = DogGE::Crypto::Hash::sha1(key);
            std::string base64Key = NetworkUtility::encodeStringToBase64(sha1Key);
            

            return connection;
        }
    }
}