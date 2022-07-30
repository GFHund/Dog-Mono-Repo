#ifndef __INVALID_CHANNEL_EXCEPTION__
#define __INVALID_CHANNEL_EXCEPTION__
#pragma once

#include <exception>
#include <string>

namespace DogGE{
    namespace Image{
        class InvalidChannelException:public std::exception{
            private:
            int mChannel;
            std::string mMessage;
            public:
            InvalidChannelException(int channel);
            const char* what() const throw();
        };
    }
}

#endif