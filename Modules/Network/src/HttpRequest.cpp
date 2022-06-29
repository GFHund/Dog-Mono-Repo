#include <HttpRequest.h>
#include <StateMachine.h>
#include <Exceptions/TransitionNotFoundException.h>
#include <Exceptions/HttpRequestParseException.h>
#include <Exceptions/HttpHeaderNotFoundException.h>

namespace DogGE{
    namespace Network{
        std::string HttpRequest::getMethod(){
            return this->mMethod;
        }
        void HttpRequest::setMethod(std::string method){
            this->mMethod = method;
        }
        
        std::string HttpRequest::getEndpoint(){
            return this->mEndpoint;
        }
        void HttpRequest::setEndpoint(std::string endpoint){
            this->mEndpoint = endpoint;
        }
        
        std::string HttpRequest::getHttpVersion(){
            return this->mHttpVersion;
        }
        void HttpRequest::setHttpVersion(std::string httpVersion){
            this->mHttpVersion = httpVersion;
        }

        std::string HttpRequest::getHttpHeader(std::string key){
            auto iter = this->mHttpHeader.find(key);
            if(iter == this->mHttpHeader.end()){
                throw HttpHeaderNotFoundException(key);
            }
            return iter->second;
        }
        void HttpRequest::setHttpHeader(std::string key,std::string value){
            auto iter = this->mHttpHeader.find(key);
            if(iter == this->mHttpHeader.end()){
                this->mHttpHeader.insert(std::pair<std::string,std::string>(key,value));
            } else {
                iter->second = value;
            }
        }

        std::string HttpRequest::getBody(){
            return this->mBody;
        }
        void HttpRequest::setBody(std::string body){
            this->mBody = body;
        }

        HttpRequest HttpRequest::parseRequest(std::string message){
            HttpRequest ret;
            StateMachine::StateMachine<char> sm;
            std::string buffer = "";
            std::string headerKey = "";
            int methodState = sm.addState();
            int endpointState = sm.addState();
            int protocolState = sm.addState();
            int endStartLineState = sm.addState();
            int headerFieldNameState = sm.addState();
            int headerFieldValueState = sm.addState();
            int endHeaderFieldState = sm.addState();
            int beginBodyFieldState = sm.addState();
            int bodyState = sm.addState();
            
            sm.addTransition(methodState,methodState,[](char i)->bool{
                return (i >= 0x41 && i<=0x5A) || (i>=0x61 && i<=0x7A);//A-Za-z
            },[&](char i){buffer += i;});
            sm.addTransition(methodState,endpointState,[](char i)->bool{
                return (i == 0x20);
            },[&](char i){
                ret.setMethod(buffer);
                buffer = "";
            });
            sm.addTransition(endpointState,endpointState,[](char i)->bool{
                //todo: weitere Erlaubte Zeichen hinzufügen
                return (i >= 0x41 && i<=0x5A) || (i>=0x61 && i<=0x7A) || (i>=0x30 && i<= 0x39) || i==0x2F || i==0x3F || i == 0x2d;//A-Za-z0-9/?-
            },[&](char i){
                buffer += i;
            });
            sm.addTransition(endpointState,protocolState,[](char i)->bool{
                return (i == 0x20);
            },[&](char i){
                ret.setEndpoint(buffer);
                buffer = "";
            });
            sm.addTransition(protocolState,protocolState,[&](char i)->bool{
                int size = buffer.size();
                switch(buffer.size()){
                    case 0: return i == 0x48;//H
                    case 1: return i == 0x54;//T
                    case 2: return i == 0x54;//T
                    case 3: return i == 0x50;//P
                    case 4: return i == 0x2F;// /
                    case 5: return (i>=0x30 && i<= 0x39);//0-9
                    case 6: return i == '.';//0x2e;//.
                    case 7: return (i>=0x30 && i<= 0x39);//0-9
                    default: return false;
                }
            },[&](char i){
                buffer += i;
            });
            sm.addTransition(protocolState,endStartLineState,[](char i)->bool{
                return i == 0x0D;// \r
            },[&](char i){
                ret.setHttpVersion(buffer);
                buffer = "";
            });
            sm.addTransition(endStartLineState,endStartLineState,[=](char i)->bool{
                if(buffer.size() == 0){
                    return i == 0x0A;// \n
                } else {
                    return false;
                }
                
            },[&](char i){
                buffer += i;
            });
            sm.addTransition(endStartLineState,headerFieldNameState,[](char i)->bool{
                return (i >= 0x41 && i<=0x5A) || (i>=0x61 && i<=0x7A) || i == 0x2d;
            },[&](char i){
                buffer = "";
                buffer += i;
            });
            sm.addTransition(headerFieldNameState,headerFieldNameState,[](char i)->bool{
                return (i >= 0x41 && i<=0x5A) || (i>=0x61 && i<=0x7A) || i == 0x2d;
            },[&](char i){
                buffer += i;
            });
            sm.addTransition(headerFieldNameState,headerFieldValueState,[](char i)->bool{
                return i == 0x3A;//:
            },[&](char i){
                headerKey = buffer;
                buffer = "";
            });
            sm.addTransition(headerFieldValueState,headerFieldValueState,[](char i)->bool{
                return (i >= 0x41 && i<=0x5A) || (i>=0x61 && i<=0x7A) || (i>= '0' && i <= '9') || i == 0x2d || i == 0x20 || i == '.' || i==':';
            },[&](char i){
                buffer += i;
            });
            sm.addTransition(headerFieldValueState,endHeaderFieldState,[](char i)->bool{
                return i == 0x0D;//\r
            },[&](char i){
                ret.setHttpHeader(headerKey,buffer);
                buffer = "";
            });
            sm.addTransition(endHeaderFieldState,endHeaderFieldState,[=](char i)->bool{
                if(buffer.size() == 0){
                    return i == 0x0A;// \n
                } else {
                    return false;
                }
            },[&](char i){
                buffer += i;
            });
            sm.addTransition(endHeaderFieldState,headerFieldNameState,[](char i)->bool{
                return (i >= 0x41 && i<=0x5A) || (i>=0x61 && i<=0x7A) || i == 0x2d;
            },[&](char i){
                buffer = "";
                buffer += i;
            });
            sm.addTransition(endHeaderFieldState,beginBodyFieldState,[](char i)->bool{
                return i == 0x0D;//\r
            },[&](char i){
                buffer ="";
            });
            sm.addTransition(beginBodyFieldState,beginBodyFieldState,[=](char i)->bool{
                if(buffer.size() == 0){
                    return i == 0x0A;// \n
                } else {
                    return false;
                }
            },[&](char i){
                buffer += i;
            });
            sm.addTransition(beginBodyFieldState,bodyState,[=](char i)->bool{
                if(buffer.size() >= 1){
                    return true;
                }
                return false;
            },[&](char i){
                buffer = "";
                buffer += i;
            });
            for(int i=0;i<message.size();i++){
                try{
                    sm.transition(message[i]);
                } catch(DogGE::StateMachine::TransitionNotFoundException<char> &e){
                    std::string error;
                    if(i < 20){
                        error = message.substr(0,40);
                    }
                    else {
                        error = message.substr(i-20,40);
                    }
                    throw HttpRequestParseException(error,e.getTransitionTrigger());
                }
            }
            ret.setBody(buffer);
            return ret;
        }
    }
}