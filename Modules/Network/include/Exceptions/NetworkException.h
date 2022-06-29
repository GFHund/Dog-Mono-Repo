#ifndef __NETWORK_EXCEPTION__
#define __NETWORK_EXCEPTION__
#pragma once

#include <exception>
#include <string>

namespace DogGE{
    namespace Network{
        class NetworkException: public std::exception{
            private:
            int mErrorCode;
            std::string mMessage;
            public:
            NetworkException(int errorCode);
            const char* what() const throw();
        };
    }
}

#endif