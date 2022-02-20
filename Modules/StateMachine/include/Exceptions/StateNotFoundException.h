#ifndef __STATE_NOT_FOUND_EXCEPTION__
#define __STATE_NOT_FOUND_EXCEPTION__
#include <exception>
#include <string>
namespace DogGE{
    namespace StateMachine{
        class StateNotFoundException:std::exception{
            private:
            int mId;
            std::string mMessage;
            public:
            StateNotFoundException(int id);
            virtual const char* what() const throw();
        };
    }
}
#endif