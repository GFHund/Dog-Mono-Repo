#ifndef __TRANSITION_NOT_FOUND_EXCEPTION__
#define __TRANSITION_NOT_FOUND_EXCEPTION__

#include <exception>
#include <string>

namespace DogGE{
    namespace StateMachine{
        template<class T>
        class TransitionNotFoundException:public std::exception{
            private:
            T mTransitionTrigger;
            unsigned int mFrom;
            std::string mMessage;
            public:
            TransitionNotFoundException(unsigned int from,T data);
            virtual const char* what() const throw();
            unsigned int getFrom();
            T getTransitionTrigger();

        };
        template<class T>
        TransitionNotFoundException<T>::TransitionNotFoundException(unsigned int from,T data){
            this->mFrom = from;
            this->mTransitionTrigger = data;
            mMessage = "Transition from id ";
            mMessage += std::to_string(this->mFrom);
            mMessage += " not found";
        }
        template<class T>
        const char* TransitionNotFoundException<T>::what() const throw(){
            return this->mMessage.c_str();
        }
        template<class T>
        unsigned int TransitionNotFoundException<T>::getFrom(){
            return this->mFrom;
        }
        template<class T>
        T TransitionNotFoundException<T>::getTransitionTrigger(){
            return this->mTransitionTrigger;
        }
    }
}

#endif