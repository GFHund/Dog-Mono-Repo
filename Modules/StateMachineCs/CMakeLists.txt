cmake_minimum_required(VERSION 3.18.0)
project(StateMachineCs VERSION 1.0.0 LANGUAGES CSharp)
set(CMAKE_VERBOSE_MAKEFILE TRUE)

SET(StateMachineCs_SOURCE
    src/StateMachine.cs
    src/StateMachineStateInterface.cs
    src/EmptyState.cs
    src/Transition.cs
    src/Exceptions/StateNotFoundException.cs
    src/Exceptions/TransitionNotFoundException.cs
)
add_library(StateMachineCs SHARED ${StateMachineCs_SOURCE})

SET(StateMachineCsTest_SOURCE
    test/StateMachineTest.cs
)

#add_executable(StateMachineCsTest ${StateMachineCsTest_SOURCE})
#target_link_libraries(StateMachineCsTest StateMachineCs)
#set_property(TARGET StateMachineCsTest
#    PROPERTY VS_PACKAGE_REFERENCES "NUnit_3.13.3"
#)
#add_test(NAME StateMachineCsTest COMMAND StateMachineCsTest)#
#
#set_property(TARGET StateMachineCsTest PROPERTY VS_DOTNET_REFERENCES
#    "System"
#    "System.Net"
#    "NUnit"
#    "NUnit.Framework"
#)