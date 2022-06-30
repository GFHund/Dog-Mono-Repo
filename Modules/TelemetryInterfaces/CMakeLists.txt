cmake_minimum_required(VERSION 3.18.0)
project(TelemetryRecorder VERSION 1.0.0)
set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TelemetryInterfaces_Source
    src/AbstractRecorderInterface.cpp
    src/RecordState.cpp
    src/ProducerConsumerRecorder.cpp
)
add_library(TelemetryInterfaces STATIC ${TelemetryInterfaces_Source})
include_directories("./include")