cmake_minimum_required(VERSION 3.18.0)
project(Tree VERSION 1.0.0)
set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(LOGGER_SOURCE
    src/Logger.cpp
    src/ConsoleOutput.cpp
    src/FileOutput.cpp
)

add_library(Logger STATIC ${LOGGER_SOURCE})
include_directories("./include")