#ifndef __HTTP_REQUEST_PARSE_EXCEPTION__
#define __HTTP_REQUEST_PARSE_EXCEPTION__

#include <exception>
#include <string>

namespace DogGE{
    namespace Network{
        class HttpRequestParseException:public std::exception{
            protected:
            std::string mMessage;
            std::string mPart;
            std::string mChar;
            public:
            HttpRequestParseException(std::string part,char Character);
            const char* what() const throw();
        };
    }
}

#endif 