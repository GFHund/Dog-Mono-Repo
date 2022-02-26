cmake_minimum_required(VERSION 3.18.0)
project(Tree VERSION 1.0.0)
set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(Window_SOURCE
    src/DogWindow.cpp
    src/Exceptions/WindowCreateException.cpp
)
find_package(OpenGL REQUIRED)
add_library(Window STATIC ${Window_SOURCE})
include_directories("./include" "../Logger/include")
target_link_libraries(Window OpenGL::GL Logger)