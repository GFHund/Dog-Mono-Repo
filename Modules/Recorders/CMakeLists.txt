cmake_minimum_required(VERSION 3.18.0)
project(Recorders VERSION 1.0.0)
set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(SOURCE 
    src/AssettoCorsaRecorder.cpp
    src/AssettoCorsaCompatizioneRecorder.cpp
)
add_library(recorders STATIC ${SOURCE})
include_directories("./include" "../Database/include" "../TelemetryInterfaces/include" "../Network/include")
target_link_libraries(recorders Database TelemetryInterfaces Network)