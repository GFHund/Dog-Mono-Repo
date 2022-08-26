cmake_minimum_required(VERSION 3.18.0)
project(Converters VERSION 1.0.0)
set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(SOURCE 
    src/F1_2022_ct_converter.cpp
    src/F1_2022_f1_converter.cpp
)

add_library(converters STATIC ${SOURCE})
include_directories("./include" "../Database/include" "../TelemetryInterfaces/include" "../F1_2022/include")
target_link_libraries(converters Database TelemetryInterfaces 2022)