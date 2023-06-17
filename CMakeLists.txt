cmake_minimum_required(VERSION 3.18.0)
project(Tree VERSION 1.0.0)
set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_WASM "Build WASM Librarys" OFF)

add_subdirectory("Modules/Utility")
add_subdirectory("Modules/Tree")
add_subdirectory("Modules/Math")
add_subdirectory("Modules/Logger")
add_subdirectory("Modules/StateMachine")

add_subdirectory("Modules/Database")
add_subdirectory("Modules/Crypto")
add_subdirectory("Modules/Network")
add_subdirectory("Modules/Json")
add_subdirectory("Modules/Window")

add_subdirectory("Modules/TelemetryInterfaces")

add_subdirectory("Modules/Converters")


add_subdirectory("Modules/Recorders")

add_subdirectory("Modules/F1_2021")
add_subdirectory("Modules/F1_2022")
add_subdirectory("Modules/TelemetryRecorder")
add_subdirectory("Modules/TelemetryConverter")
#add_subdirectory("Modules/CTelemetry2Fe")
add_subdirectory("Modules/F1GameParserGenerator")
#add_subdirectory("Modules/CTelemetry2Electron")
add_subdirectory("Modules/TelemetryWsServer")
add_subdirectory("Modules/WebsocketClient")


if(MSVC)
add_subdirectory("Modules/StateMachineCs")
add_subdirectory("Modules/ConvertersCsInterface")
add_subdirectory("Modules/TelemetryWsServerCs")
endif()