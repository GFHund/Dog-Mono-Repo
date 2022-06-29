cmake_minimum_required(VERSION 3.18.0)
project(2022 VERSION 1.0.0)
set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(SOURCE
    src/DataClass/CarDamageData.cpp
src/DataClass/CarDamagePackage.cpp
src/DataClass/CarMotionData.cpp
src/DataClass/CarSetupData.cpp
src/DataClass/CarSetupsPackage.cpp
src/DataClass/CarStatusData.cpp
src/DataClass/CarStatusPackage.cpp
src/DataClass/CarTelemetryData.cpp
src/DataClass/CarTelemetryPackage.cpp
src/DataClass/FinalClassificationData.cpp
src/DataClass/FinalClassificationPackage.cpp
src/DataClass/Header.cpp
src/DataClass/LapData.cpp
src/DataClass/LapDataPackage.cpp
src/DataClass/LapHistoryData.cpp
src/DataClass/LobbyInfoData.cpp
src/DataClass/LobbyInfoPackage.cpp
src/DataClass/MarshalZone.cpp
src/DataClass/MotionPackage.cpp
src/DataClass/ParticipantsData.cpp
src/DataClass/ParticipantsPackage.cpp
src/DataClass/SessionHistoryPackage.cpp
src/DataClass/SessionPackage.cpp
src/DataClass/TyreStintHistoryData.cpp
src/DataClass/WeatherForecastSample.cpp
src/F1DataEntity_2022.cpp
src/Recorder_2022.cpp
src/Exceptions/ValidationException.cpp

)
add_library(2022 STATIC ${SOURCE})
include_directories("./include" "../Database/include" "../TelemetryInterfaces/include" "../Network/include")
target_link_libraries(2022 Network Database)
            