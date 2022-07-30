#ifndef __MATH_OPERATION_FORBIDDEN_EXCEPTION__
#define __MATH_OPERATION_FORBIDDEN_EXCEPTION__
#include <exception>
#include <string>


namespace DogGE{
    namespace Math{
        class MathOperationForbiddenException:public std::exception{
            std::string mMessage;
            public:
            MathOperationForbiddenException(std::string message);
            virtual const char* what() const throw();
        };
    }
}
#endif