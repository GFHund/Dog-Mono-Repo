#ifndef __HTTP_HEADER_NOT_FOUND_EXCEPTION__
#define __HTTP_HEADER_NOT_FOUND_EXCEPTION__
#pragma once

#include <exception>
#include <string>

namespace DogGE{
    namespace Network{
        class HttpHeaderNotFoundException: public std::exception{
            protected:
            std::string mMessage;
            std::string mHeaderName;
            public:
            HttpHeaderNotFoundException(std::string headerName);
            const char* what() const throw();
        };
    }
}

#endif