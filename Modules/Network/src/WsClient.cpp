#include <WsClient.h>

#include <HttpRequest.h>

namespace DogGE{
    namespace Network{
        void WsClient::performHandshake(){
            HttpRequest request;
            request.setMethod("GET");
            request.setEndpoint("/");
            request.setHttpVersion("1.1");
            request.setBody("");
            request.setHttpHeader("Host","");
            request.setHttpHeader("Upgrade","websocket");
            request.setHttpHeader("Connection","Upgrade");
            request.setHttpHeader("Sec-WebSocket-Key","");
        }
    }
}