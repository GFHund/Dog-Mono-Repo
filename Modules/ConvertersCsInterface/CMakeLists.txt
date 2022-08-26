cmake_minimum_required(VERSION 3.18.0)
project(ConvertersCsInterface VERSION 1.0.0)
set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(SOURCE 
    src/F1_2022_ct_converter_wrapper.cpp
    #src/F1_2022_f1_converter.cpp
)
add_library(ConvertersCsInterface SHARED ${SOURCE})
include_directories("./include" "./../Converters/include" "../Database/include" "../TelemetryInterfaces/include")
#set_target_properties(ConvertersCsInterface PROPERTIES COMMON_LANGUAGE_RUNTIME "")
target_link_libraries(ConvertersCsInterface converters)