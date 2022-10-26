cmake_minimum_required(VERSION 3.18.0)
project(Math VERSION 1.0.0)
set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(NETWORK_SOURCE
    src/AbstractNetwork.cpp
    src/AbstractClient.cpp
    src/AbstractServer.cpp
    src/ClientConnection.cpp
    src/UdpClient.cpp
    src/UdpServer.cpp
    src/TcpClient.cpp
    src/TcpServer.cpp
    src/WsServer.cpp
    src/HttpRequest.cpp
    src/HttpResponse.cpp
    src/NetworkUtility.cpp
    src/Exceptions/NetworkException.cpp
    src/Exceptions/HttpRequestParseException.cpp
    src/Exceptions/HttpHeaderNotFoundException.cpp
    src/Exceptions/NothingRecivedException.cpp
    src/Exceptions/ConvertWebsocketMessageException.cpp
)
add_library(Network STATIC ${NETWORK_SOURCE})
include_directories("./include" "./vendor" "../StateMachine/include" "../Crypto/include" "../Utility/include")
target_link_libraries(
    Network
    StateMachine
    Crypto
    Utility
    ws2_32
)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()
add_executable(Network_test
    test/HttpRequestTest.cpp
    test/NetworkUtilityTest.cpp
    test/WebsocketTest.cpp
)
target_link_libraries(
    Network_test
    gtest_main
    Network
)
include(GoogleTest)
gtest_discover_tests(Network_test)