#include <gtest/gtest.h>
#include <StateMachine.h>
#include <StateMachineStateInterface.h>
#include "TestStates/CustomTestState.h"


TEST(StateMachine,Constructor){
    DogGE::StateMachine::StateMachine<int> sm;
    EXPECT_EQ(sm.getCurrentStateId(),0);
}
TEST(StateMachine,addState1){
    DogGE::StateMachine::StateMachine<int> sm;
    int id = sm.addState();
    DogGE::StateMachine::StateMachineStateInterface* state = sm.getState(id);
    EXPECT_EQ(state->getStateMachineId(),0);
}
TEST(StateMachine,addState2){
    DogGE::StateMachine::StateMachine<int> sm;
    CustomTestState* testState = new CustomTestState();
    int id = sm.addState(testState);
    DogGE::StateMachine::StateMachineStateInterface* state = sm.getState(id);
    EXPECT_EQ(state->getStateMachineId(),0);
    delete testState;
}

TEST(StateMachine,transition){
    DogGE::StateMachine::StateMachine<int> sm;
    CustomTestState* state1 = new CustomTestState();
    CustomTestState* state2 = new CustomTestState();
    int id1 = sm.addState(state1);
    int id2 = sm.addState(state2);
    sm.addTransition(id1,id2,[](int i)->bool{
        return i==1;
    },[](int i){});
    sm.addTransition(id2,id1,[](int i)->bool{
        return i==2;
    },[](int i){});
    sm.transition(1);
    EXPECT_EQ(sm.getCurrentStateId(),id2);
    EXPECT_EQ(state1->getCountEnterState(),0);
    EXPECT_EQ(state1->getCountLeaveState(),1);
    EXPECT_EQ(state1->getCountUpdateState(),0);
    EXPECT_EQ(state2->getCountEnterState(),1);
    EXPECT_EQ(state2->getCountLeaveState(),0);
    EXPECT_EQ(state2->getCountUpdateState(),0);
    sm.transition(2);
    EXPECT_EQ(sm.getCurrentStateId(),id1);
    EXPECT_EQ(state1->getCountEnterState(),1);
    EXPECT_EQ(state1->getCountLeaveState(),1);
    EXPECT_EQ(state1->getCountUpdateState(),0);
    EXPECT_EQ(state2->getCountEnterState(),1);
    EXPECT_EQ(state2->getCountLeaveState(),1);
    EXPECT_EQ(state2->getCountUpdateState(),0);
    delete state1;
    delete state2;
}
TEST(StateMachine,updateTransition){
    DogGE::StateMachine::StateMachine<int> sm;
    CustomTestState* state1 = new CustomTestState();
    CustomTestState* state2 = new CustomTestState();
    int id1 = sm.addState(state1);
    int id2 = sm.addState(state2);
    sm.addTransition(id1,id2,[](int i)->bool{
        return i==1;
    },[](int i){});
    sm.addTransition(id2,id1,[](int i)->bool{
        return i==2;
    },[](int i){});
    sm.updateCurrentState();
    EXPECT_EQ(state1->getCountUpdateState(),1);
    EXPECT_EQ(state2->getCountUpdateState(),0);
    sm.transition(1);
    sm.updateCurrentState();
    EXPECT_EQ(state1->getCountUpdateState(),1);
    EXPECT_EQ(state2->getCountUpdateState(),1);
    sm.transition(2);
    sm.updateCurrentState();
    EXPECT_EQ(state1->getCountUpdateState(),2);
    EXPECT_EQ(state2->getCountUpdateState(),1);
    delete state1;
    delete state2;
}