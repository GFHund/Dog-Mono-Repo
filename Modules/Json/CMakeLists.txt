cmake_minimum_required(VERSION 3.18.0)
project(Math VERSION 1.0.0)
set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(Json_SOURCE
    src/AbstractType.cpp
    src/JsonParser.cpp
    src/ValueType.cpp
    src/PropertyType.cpp
    src/Exceptions/ConvertDataTypeException.cpp
)
add_library(Json STATIC ${Json_SOURCE})
target_link_libraries(
    Json
    StateMachine
    Tree
)
include_directories("./include" "./../StateMachine/include" "./../Tree/include")
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()
add_executable(Json_test
    test/ParseJsonTest.cpp
)
target_link_libraries(
    Json_test
    gtest_main
    Json
)
include(GoogleTest)
gtest_discover_tests(Json_test)