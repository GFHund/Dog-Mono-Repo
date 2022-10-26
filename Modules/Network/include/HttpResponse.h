#ifndef __HTTP_RESPONSE__
#define __HTTP_RESPONSE__
#pragma once

#include <string>
#include <map>

namespace DogGE{
    namespace Network{
        class HttpResponse{
            private:
            int mHttpCode;
            std::map<std::string,std::string> mHttpHeader;
            std::string mContent;
            public:
            HttpResponse(int httpCode);
            void addHeader(std::string key,std::string value);
            void setContent(std::string content);
            std::string toString();
        };
    }
}
#endif