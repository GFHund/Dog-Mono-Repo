#ifndef __HTTP_REQUEST__
#define __HTTP_REQUEST__
#pragma once

#include <string>
#include <map>

namespace DogGE{
    namespace Network{
        class HttpRequest{
            protected:
            std::string mMethod;
            std::string mEndpoint;
            std::string mHttpVersion;
            std::map<std::string,std::string> mHttpHeader;
            std::string mBody;
            public:
            std::string getMethod();
            void setMethod(std::string method);
            
            std::string getEndpoint();
            void setEndpoint(std::string endpoint);
            
            std::string getHttpVersion();
            void setHttpVersion(std::string httpVersion);

            std::string getHttpHeader(std::string key);
            void setHttpHeader(std::string key,std::string value);

            std::string getBody();
            void setBody(std::string body);

            static HttpRequest parseRequest(std::string message);

        };
    }
}


#endif