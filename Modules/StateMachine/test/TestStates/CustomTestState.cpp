#include "CustomTestState.h"

CustomTestState::CustomTestState(){
    this->countEnterState = 0;
    this->countLeaveState = 0;
    this->countUpdateState = 0;
}

void CustomTestState::enterState(){
    this->countEnterState++;
}
void CustomTestState::leaveState(){
    this->countLeaveState++;
}

void CustomTestState::updateState(){
    this->countUpdateState++;
}

int CustomTestState::getCountEnterState(){
    return this->countEnterState;
}
int CustomTestState::getCountLeaveState(){
    return this->countLeaveState;
}
int CustomTestState::getCountUpdateState(){
    return this->countUpdateState;
}