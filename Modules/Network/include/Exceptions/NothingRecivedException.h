#ifndef __NOTHING_RECIVED_EXCEPTION__
#define __NOTHING_RECIVED_EXCEPTION__
#pragma once

#include <exception>
#include <string>

namespace DogGE{
    namespace Network{
        class NothingRecivedException: public std::exception{
            private:
            std::string mMessage;
            public:
            const char* what() const throw();
        };
    }
}

#endif