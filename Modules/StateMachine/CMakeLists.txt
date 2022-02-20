cmake_minimum_required(VERSION 3.18.0)
project(Math VERSION 1.0.0)
set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(StateMachine_SOURCE
    src/StateMachine.cpp
    src/StateMachineStateInterface.cpp
    src/EmptyState.cpp
    src/Exceptions/StateNotFoundException.cpp
)
add_library(StateMachine STATIC ${StateMachine_SOURCE})
include_directories("./include")
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()
add_executable(StateMachine_test
    test/TestStates/CustomTestState.cpp
    test/StateMachineTest.cpp
    test/EmptyStateTest.cpp
    test/TransitionTest.cpp
)
target_link_libraries(
    StateMachine_test
    gtest_main
    StateMachine
)
include(GoogleTest)
gtest_discover_tests(StateMachine_test)