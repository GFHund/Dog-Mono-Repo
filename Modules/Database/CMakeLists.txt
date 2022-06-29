cmake_minimum_required(VERSION 3.18.0)
project(Database VERSION 1.0.0)
set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_definitions(SQLITE_ENABLE_COLUMN_METADATA=1)

SET(DATABASE_SOURCE
    src/DatabaseBuilder.cpp
    src/Database.cpp
    src/AbstractEntity.cpp
    src/QueryBuilder.cpp
    src/PrepareStatement.cpp
    src/Exceptions/DatabaseNotFoundException.cpp
    src/Exceptions/ConvertErrorException.cpp
    src/Exceptions/SQLErrorException.cpp
    src/Exceptions/TableNotFoundException.cpp
    src/Exceptions/DatabaseErrorException.cpp
    
    vendor/sqlite3/sqlite3.c
)
add_library(Database STATIC ${DATABASE_SOURCE})
include_directories("./include")
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(rwTest
    manualTest/rwTest.cpp
    test/Entity/TestEntity.cpp
)
target_link_libraries(
    rwTest
    Database
)


enable_testing()

add_executable(
    database_test
    test/DatabaseBuilderTest.cpp
    test/DatabaseTest.cpp
    test/QueryBuilderTest.cpp
    test/Entity/TestEntity.cpp
)
target_link_libraries(
    database_test
    gtest_main
    Database
)
include(GoogleTest)
gtest_discover_tests(database_test)