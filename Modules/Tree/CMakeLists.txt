cmake_minimum_required(VERSION 3.18.0)
project(Tree VERSION 1.0.0)
set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(TREE_SOURCE
    src/AbstractTreeNode.cpp
    src/ArrayTreeNode.cpp
    src/LinkTreeNode.cpp
    src/Exceptions/NodeNotFoundException.cpp
    src/Exceptions/NodeHasNoDataBagException.cpp
)

add_library(Tree STATIC ${TREE_SOURCE})
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
    tree_test
    test/ArrayTreeTest.cpp
    test/LinkTreeTest.cpp
)
target_link_libraries(
    tree_test
    gtest_main
    Tree
)
include(GoogleTest)
gtest_discover_tests(tree_test)