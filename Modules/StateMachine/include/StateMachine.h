#ifndef __STATE_MACHINE__
#define __STATE_MACHINE__

#include <vector>
#include <functional>
#include <StateMachineStateInterface.h>
#include <EmptyState.h>
#include <Transition.h>
#include <Exceptions/StateNotFoundException.h>
#include <Exceptions/TransitionNotFoundException.h>


namespace DogGE{
    namespace StateMachine{

        
        template<class T>
        class StateMachine{
            private:
            std::vector<EmptyState*> mInstanciatedStates;//Keep Track of internally created States
            std::vector<StateMachineStateInterface*> mStates;
            std::vector<Transition<T>> mTransitions;
            unsigned int mCurrentStateId;
            unsigned int mIdCounter;
            public:
            StateMachine();
            ~StateMachine();

            int addState();
            int addState(StateMachineStateInterface* data);
            StateMachineStateInterface* getState(unsigned int id);

            int getCurrentStateId();
            
            void addTransition(unsigned int fromState,unsigned int toState,std::function<bool(T)> trigger,std::function<void(T)> transition);
            void transition(T trigger);
            
            StateMachineStateInterface* getCurrentStateData();
            void updateCurrentState();
            
        };
        

        template<class T>
        StateMachine<T>::StateMachine(){
            mIdCounter = 0;
            mCurrentStateId = 0;
        }

        template<class T>
        StateMachine<T>::~StateMachine(){
            for(int i=0;i<mInstanciatedStates.size();i++){
                delete mInstanciatedStates[i];
            }
        }
        
        template<class T>
        int StateMachine<T>::addState(){
            EmptyState* es = new EmptyState();
            int id = mIdCounter;
            mIdCounter++;
            es->setStateMachineId(id);
            //mInstanciatedStates.push_back(es);
            mStates.push_back(es);
            return id;
        }

        template<class T>
        int StateMachine<T>::addState(StateMachineStateInterface* newState){
            int id = mIdCounter;
            mIdCounter++;
            newState->setStateMachineId(id);
            mStates.push_back(newState);
            return id;
        }

        template<class T>
        StateMachineStateInterface* StateMachine<T>::getState(unsigned int id){
            for(auto state:mStates){
                if(state->getStateMachineId() == id){
                    return state;
                }
            }
            throw StateNotFoundException(id);
        }

        template<class T>
        int StateMachine<T>::getCurrentStateId(){
            return this->mCurrentStateId;
        }

        template<class T>
        void StateMachine<T>::addTransition(unsigned int fromState,unsigned int toState,std::function<bool(T)> trigger,std::function<void(T)> transition){
            this->mTransitions.push_back(Transition<T>(fromState,toState,trigger,transition));
        }

        template <class T>
        void StateMachine<T>::transition(T data){
            for(auto transition:mTransitions){
                if(transition.getFrom() == mCurrentStateId){
                    if(transition.callTrigger(data)){
                        StateMachineStateInterface* state = this->getCurrentStateData();
                        state->leaveState();
                        mCurrentStateId = transition.getTo();
                        state = this->getCurrentStateData();
                        transition.callTransition(data);
                        state->enterState();
                        return;
                    }
                }
            }
            throw TransitionNotFoundException<T>(mCurrentStateId,data);
        }
        template<class T>
        StateMachineStateInterface* StateMachine<T>::getCurrentStateData(){
            return this->getState(this->mCurrentStateId);
        }

        template<class T>
        void StateMachine<T>::updateCurrentState(){
            StateMachineStateInterface* currentState = this->getCurrentStateData();
            currentState->updateState();
        }
    }
}
#endif