#ifndef __EMPTY_STATE__
#define __EMPTY_STATE__

#include <StateMachineStateInterface.h>

namespace DogGE{
    namespace StateMachine{
        class EmptyState: public StateMachineStateInterface{
            public:
            void enterState() override;
            void leaveState() override;
            void updateState() override;
        };
    }
}

#endif