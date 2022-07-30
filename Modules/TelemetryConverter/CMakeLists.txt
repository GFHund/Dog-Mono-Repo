cmake_minimum_required(VERSION 3.18.0)
project(TelemetryConverter VERSION 1.0.0)
set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TelemetryConverter_Source
    src/main.cpp
    src/Exceptions/ConverterNotFoundException.cpp
    src/Exceptions/ConverterNotSuitable.cpp
    vendor/cxxopts/cxxopts.hpp
)
add_executable(TelemetryConverter ${TelemetryConverter_Source})
include_directories("./include")
target_link_libraries(
    TelemetryRecorder
    TelemetryInterfaces
    2021
    Database
)
include_directories("./include" "./../TelemetryInterfaces/include" "./../F1_2021/include" "./../Database/include")