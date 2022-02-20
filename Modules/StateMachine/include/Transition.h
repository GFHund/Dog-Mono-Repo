#ifndef __TRANSITION__
#define __TRANSITION__

#include <functional>

namespace DogGE{
    namespace StateMachine{
        template<class T>
        class Transition{
            protected:
            unsigned int mFromId;
            unsigned int mToId;
            std::function<bool(T)> mTrigger;
            std::function<void(T)> mTransition;
            public:
            Transition(unsigned int fromState,unsigned int toState,std::function<bool(T)> trigger,std::function<void(T)> transition);
            unsigned int getFrom();
            unsigned int getTo();
            bool callTrigger(T data);
            void callTransition(T data);
        };

        template<class T>
        Transition<T>::Transition(unsigned int fromState,unsigned int toState,std::function<bool(T)> trigger,std::function<void(T)> transition){
            this->mFromId = fromState;
            this->mToId = toState;
            this->mTrigger = trigger;
            this->mTransition = transition;
        }
        template<class T>
        unsigned int Transition<T>::getFrom(){
            return this->mFromId;
        }
        template<class T>
        unsigned int Transition<T>::getTo(){
            return this->mToId;
        }
        template<class T>
        bool Transition<T>::callTrigger(T data){
            return this->mTrigger(data);
        }
        template<class T>
        void Transition<T>::callTransition(T data){
            this->mTransition(data);
        }
    }
}
#endif