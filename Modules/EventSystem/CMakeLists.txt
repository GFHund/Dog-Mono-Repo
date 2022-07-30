cmake_minimum_required(VERSION 3.18.0)
project(Tree VERSION 1.0.0)
set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(EVENT_SYSTEM_SOURCE
    src/EventManager.cpp
    src/EventParam.cpp
)

add_library(Event_System STATIC ${EVENT_SYSTEM_SOURCE})
include_directories("./include")