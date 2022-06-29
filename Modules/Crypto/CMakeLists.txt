cmake_minimum_required(VERSION 3.18.0)
project(Crypto VERSION 1.0.0)
set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(CRYPTO_SOURCE
    src/Hash.cpp
)
add_library(Crypto STATIC ${CRYPTO_SOURCE})
include_directories("./include")

add_executable(shaTest proposalCode/main.c proposalCode/sha1.c)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
    crypto_test
    test/HashTest.cpp
)
target_link_libraries(
    crypto_test
    gtest_main
    Crypto
)
include(GoogleTest)
gtest_discover_tests(crypto_test)