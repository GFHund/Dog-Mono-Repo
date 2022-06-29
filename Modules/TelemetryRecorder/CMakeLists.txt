cmake_minimum_required(VERSION 3.18.0)
project(TelemetryRecorder VERSION 1.0.0)
set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TelemetryRecorder_Source
    src/main.cpp
    vendor/cxxopts/cxxopts.hpp
)

add_executable(TelemetryRecorder ${TelemetryRecorder_Source})

target_link_libraries(
    TelemetryRecorder
    Network
    TelemetryInterfaces
    2021
    2022
    Database
)
include_directories("./include" "./../TelemetryInterfaces/include" "./../F1_2021/include" "./../F1_2022/include" "./../Network/include" "./../Database/include")