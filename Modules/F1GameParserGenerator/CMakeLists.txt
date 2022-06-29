cmake_minimum_required(VERSION 3.18.0)
project(Tree VERSION 1.0.0)
set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(F1GameParserGenerator_SOURCE
    src/main.cpp
    src/ParserGenerator.cpp
    src/F1Spec.cpp
    src/Packages.cpp
    src/Fields.cpp
    src/F1SpecBuilder.cpp
    src/Generators/AbstractGenerator.cpp
    src/Generators/SourceGenerator.cpp
    src/Generators/GenerateDataClassHeader.cpp
    src/Generators/GenerateDataClassSource.cpp
    src/Generators/GenerateCMakeList.cpp
    src/Generators/GenerateRecorderHeader.cpp
    src/Generators/GenerateRecorderSource.cpp
    src/Generators/GenerateDataEntityHeader.cpp
    src/Generators/GenerateDataEntitySource.cpp
    src/Generators/GenerateExceptionHeader.cpp
    src/Generators/GenerateExceptionSource.cpp
    src/Generators/GenerateConverterHeader.cpp
    src/Generators/GenerateConverterSource.cpp
    src/Exceptions/FileNotFoundException.cpp
    src/Exceptions/PackageNotFoundException.cpp
    src/Exceptions/DataTypeNotFoundException.cpp
    #vendor/cxxopts/cxxopts.hpp
    #vendor/json/json.hpp
    #vendor/mustache/mustache.hpp
)
SET(F1GameParserGeneratorTest_SOURCE
    src/F1Spec.cpp
    src/Packages.cpp
    src/Fields.cpp
    src/F1SpecBuilder.cpp
    src/Exceptions/FileNotFoundException.cpp
    src/Exceptions/PackageNotFoundException.cpp
    src/Exceptions/DataTypeNotFoundException.cpp
)
configure_file(F1Spec/2021.json F1Spec/2021.json COPYONLY)
configure_file(F1Spec/2022.json F1Spec/2022.json COPYONLY)
configure_file(template/CMakeListsTemplate.txt template/CMakeListsTemplate.txt COPYONLY)
configure_file(template/ConvertBinary2ObjectTemplate.cpp template/ConvertBinary2ObjectTemplate.cpp COPYONLY)
configure_file(template/ConvertBinary2ObjectTemplate.h template/ConvertBinary2ObjectTemplate.h COPYONLY)
configure_file(template/F1DataClassTemplate.cpp template/F1DataClassTemplate.cpp COPYONLY)
configure_file(template/F1DataClassTemplate.h template/F1DataClassTemplate.h COPYONLY)
configure_file(template/RecorderTemplate.cpp template/RecorderTemplate.cpp COPYONLY)
configure_file(template/RecorderTemplate.h template/RecorderTemplate.h COPYONLY)
configure_file(template/F1DataEntityTemplate.h template/F1DataEntityTemplate.h COPYONLY)
configure_file(template/F1DataEntityTemplate.cpp template/F1DataEntityTemplate.cpp COPYONLY)
configure_file(template/ExceptionTemplate.h template/ExceptionTemplate.h COPYONLY)
configure_file(template/ExceptionTemplate.cpp template/ExceptionTemplate.cpp COPYONLY)

add_executable(F1GameParserGenerator ${F1GameParserGenerator_SOURCE})
add_library(F1GameParserGeneratorLib STATIC ${F1GameParserGeneratorTest_SOURCE})

target_link_libraries(
    F1GameParserGenerator
    Utility
)
target_link_libraries(
    F1GameParserGeneratorLib
    Utility
)

include_directories("./include" "./../Utility/include")

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
    F1GameParserGenerator_test
    test/F1SpecBuilderTest.cpp
    
)
target_link_libraries(
    F1GameParserGenerator_test
    gtest_main
    F1GameParserGeneratorLib
)
include(GoogleTest)
gtest_discover_tests(F1GameParserGenerator_test)