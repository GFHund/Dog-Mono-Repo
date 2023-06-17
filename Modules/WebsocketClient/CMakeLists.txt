cmake_minimum_required(VERSION 3.18.0)
project(WebsocketClient VERSION 1.0.0)
set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(WebsocketClient_Source
    src/main.cpp
)
add_executable(WebsocketClient ${WebsocketClient_Source})

target_link_libraries(
    WebsocketClient
    Network
)
include_directories("./include" "./../Network/include")