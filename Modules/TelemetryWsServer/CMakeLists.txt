cmake_minimum_required(VERSION 3.18.0)
project(TelemetryWsServer VERSION 1.0.0)
set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(TELEMETRY_WS_SERVER_SOURCE
src/main.cpp
src/TelemetryController.cpp
src/CommandParser.cpp
)

add_executable(TelemetryWsServer ${TELEMETRY_WS_SERVER_SOURCE})

target_link_libraries(
    TelemetryWsServer
    Network
    TelemetryInterfaces
    2021
    2022
    Database
    StateMachine
)

include_directories("./include" "./../F1_2021/include" "./../F1_2022/include" "./../Network/include" "./../Database/include" "./../StateMachine/include")