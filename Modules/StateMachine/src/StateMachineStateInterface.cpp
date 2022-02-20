#include <StateMachineStateInterface.h>

namespace DogGE{
    namespace StateMachine{
        void StateMachineStateInterface::setStateMachineId(unsigned int id){
            this->mStateMachineId = id;
        }
        unsigned int StateMachineStateInterface::getStateMachineId(){
            return this->mStateMachineId;
        }
    }
}
