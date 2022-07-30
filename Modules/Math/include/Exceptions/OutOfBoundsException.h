#ifndef __OUT_OF_BOUNDS_EXCEPTION__
#define __OUT_OF_BOUNDS_EXCEPTION__
#include <exception>

namespace DogGE{
    namespace Math{
        class OutOfBoundsException:public std::exception{
            private:
            int mMaxAllowedValue;
            int mGivenValue;

            public:
            OutOfBoundsException(int maxAllowedValue,int givenValue);
            virtual const char* what() const throw();
        };
    }
}
#endif