#ifndef __CONVERT_WEBSOCKET_MESSAGE_EXCEPTION__
#define __CONVERT_WEBSOCKER_MESSAGE_EXCEPTION__
#pragma once

#include <exception>
#include <string>

namespace DogGE{
    namespace Network{
        class ConvertWebsocketMessageException: public std::exception{
            protected:
            std::string mMessage;
            public:
            ConvertWebsocketMessageException(std::string message);
            const char* what() const throw();
        };
    }
}

#endif 