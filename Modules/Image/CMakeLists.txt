cmake_minimum_required(VERSION 3.18.0)
project(Image VERSION 1.0.0)
set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(Image_SOURCE
    src/Image.cpp
    src/Exceptions/InvalidChannelException.cpp
    src/Exceptions/UnsupportedConvertException.cpp
)
add_library(Image STATIC ${Image_SOURCE})
include_directories("./include" "./../Math/include")
target_link_libraries(
    Image
    Math
)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
    image_test
    test/ImageTest.cpp
    
    
)
target_link_libraries(
    image_test
    gtest_main
    Image
)
include(GoogleTest)
gtest_discover_tests(image_test)