#include <WsServer.h>
#include <array>
#include <HttpRequest.h>
#include <HttpResponse.h>
#include <NetworkUtility.h>
#include <StringUtility.h>
#include <Hash.h>
#include <iostream>
#include <cstring>
#include <sha1.h>


namespace DogGE{
    namespace Network{
        ClientConnection* WsServer::acceptConnection(){
            ClientConnection* connection = AbstractServer::acceptConnection();
            if(connection == nullptr){
                return nullptr;
            }
            std::cout << "Accept Connection" << std::endl;
            std::array<char,4096> buffer = connection->recvData<4096>();
            std::string message = std::string(buffer.data());
            if(message[0] != 'G' || message[1] != 'E' || message[2] != 'T'){
                return connection;
            }
            HttpRequest request = HttpRequest::parseRequest(message);
            
            std::string key = request.getHttpHeader("Sec-WebSocket-Key");
            key = DogGE::Utility::StringUtility::trim(key);
            std::cout << "Key " << key << std::endl;
            key += "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
            std::cout << "Key With Padding " << key << std::endl;
            //std::string sha1Key = DogGE::Crypto::Hash::sha1(key);
            Chocobo1::SHA1 sha1;
            sha1.addData(key.c_str(),key.size());
            sha1.finalize();
            //std::string sha1Key = sha1.toString();
            auto sha1Key = sha1.toArray();

            for(int i=0;i<20;i++){
                std::cout << std::hex << int(sha1Key[i]) << std::endl;
            }
            //std::cout << "sha1 Key " << sha1Key << std::endl;
            std::string base64Key = NetworkUtility::encodeDataToBase64<20>(sha1Key);
            std::cout << "base64 Key " << base64Key << std::endl;
            
            HttpResponse response(101);
            response.addHeader("Upgrade","websocket");
            response.addHeader("Connection","Upgrade");
            response.addHeader("Sec-WebSocket-Accept",base64Key);
            std::array<char,2000> sendBuffer;
            std::string responseString = response.toString();
            std::memcpy(sendBuffer.data(),responseString.c_str(),responseString.size());
            connection->sendData<2000>(sendBuffer);

            return nullptr;
        }
    }
}