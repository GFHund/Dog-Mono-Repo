#include <HttpResponse.h>

namespace DogGE{
    namespace Network{
        HttpResponse::HttpResponse(int httpCode){
            this->mHttpCode = httpCode;
            this->mContent = "";
        }
        void HttpResponse::addHeader(std::string key,std::string value){
            this->mHttpHeader.insert(std::pair<std::string,std::string>(key,value));
        }
        void HttpResponse::setContent(std::string content){
            this->mContent = content;
        }
        std::string HttpResponse::toString(){
            std::string ret = "HTTP/1.1 ";
            ret += std::to_string(this->mHttpCode);
            switch(this->mHttpCode){
                case 101:
                ret += " Switching Protocols\n";
                break;
                case 200:
                case 400:
                break;
            }
            for(auto iter: this->mHttpHeader){
                ret += iter.first;
                ret += ": ";
                ret += iter.second;
                ret += "\n";
            }
            ret += "\n";
            ret += this->mContent;
            return ret;
        }
    }
}