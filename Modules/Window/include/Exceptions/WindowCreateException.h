#ifndef __WINDOW_CREATE_EXCEPTION__
#define __WINDOW_CREATE_EXCEPTION__

#include <exception>
#include <string>
namespace DogGE{
    namespace Window{
        class WindowCreateException:public std::exception{
            private:
            std::string mMessage;
            public:
            WindowCreateException(std::string message);
            virtual const char* what() const throw();
        };
    }
}

#endif