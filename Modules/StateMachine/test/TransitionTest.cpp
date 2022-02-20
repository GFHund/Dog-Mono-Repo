#include <gtest/gtest.h>
#include <Transition.h>

TEST(Transition,constructor){
    DogGE::StateMachine::Transition<int> transition = DogGE::StateMachine::Transition<int>(0,1,[](int i){return true;},[](int i){});
    EXPECT_EQ(transition.getFrom(),0);
    EXPECT_EQ(transition.getTo(),1);
}
TEST(Transition,callTrigger){
    DogGE::StateMachine::Transition<int> transition = DogGE::StateMachine::Transition<int>(0,1,[](int i){
        if(i == 5){
            return true;
        } 
        return false;
    },[](int i){});
    
    EXPECT_TRUE(transition.callTrigger(5));
    EXPECT_FALSE(transition.callTrigger(8));
}
TEST(Transition,callTransition){
    int test = 5;
    DogGE::StateMachine::Transition<int> transition = DogGE::StateMachine::Transition<int>(0,1,[](int i){return false;},[&](int i){test += i;});
    transition.callTransition(4);
    EXPECT_EQ(test,9);
    
}