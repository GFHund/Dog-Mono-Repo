cmake_minimum_required(VERSION 3.18.0)
project(Utility VERSION 1.0.0)
set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(UtilitySrc
    src/StringUtility.cpp
    src/VectorUtility.cpp
)

add_library(Utility STATIC ${UtilitySrc})
include_directories("./include")

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
    Utility_test
    test/StringUtilityTest.cpp
    test/VectorUtilityTest.cpp
)
target_link_libraries(
    Utility_test
    gtest_main
    Utility
)
include(GoogleTest)
gtest_discover_tests(Utility_test)