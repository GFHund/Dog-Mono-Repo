#ifndef __STATE_MACHINE_STATE_INTERFACE__
#define __STATE_MACHINE_STATE_INTERFACE__

//#include <StateMachine.h>
  
namespace DogGE{
    namespace StateMachine{
        class StateMachineStateInterface{
            protected:
            unsigned int mStateMachineId;
            public:
            void setStateMachineId(unsigned int id);
            unsigned int getStateMachineId();

            virtual void enterState() = 0;
            virtual void leaveState() = 0;
            //virtual void updateState(StateMachine* stateMachine) = 0;
            virtual void updateState() = 0;
        };
    }
}

#endif