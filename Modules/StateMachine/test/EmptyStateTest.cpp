#include <gtest/gtest.h>
#include <EmptyState.h>

TEST(EmptyState,getSetId){
    DogGE::StateMachine::EmptyState es;
    es.setStateMachineId(5);
    EXPECT_EQ(es.getStateMachineId(),5);
}