#ifndef __CUSTOM_TEST_STATE__
#define __CUSTOM_TEST_STATE__
#include <StateMachineStateInterface.h>

class CustomTestState:public DogGE::StateMachine::StateMachineStateInterface{
    private:
    int countEnterState;
    int countLeaveState;
    int countUpdateState;
    public:
    CustomTestState();

    void enterState() override;
    void leaveState() override;
    void updateState() override;

    int getCountEnterState();
    int getCountLeaveState();
    int getCountUpdateState();
};

#endif