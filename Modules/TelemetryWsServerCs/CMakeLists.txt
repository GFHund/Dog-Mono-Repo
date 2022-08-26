cmake_minimum_required(VERSION 3.18.0)
project(TelemetryWsServerCs VERSION 1.0.0 LANGUAGES CSharp)
set(CMAKE_VERBOSE_MAKEFILE TRUE)

add_executable(
    TelemetryWsServerCs
    src/Program.cs
    src/WebSocket.cs
    src/AbstractWebSocketConnection.cs
    src/TelemetryWebSocketConnection.cs
    src/AbstractWebSocketConnectionBuilder.cs
    src/TelemetryWebSocketConnectionBuilder.cs
    src/AbstractCommand.cs
    src/ConvertCommand.cs
    src/ConvertOptionsCommand.cs
    src/NotInitializedCommand.cs
    src/Exceptions/ConvertWebsocketMessageException.cs

    src/F1_2022_Ct_Converter.cs
)

#set_property(TARGET Example PROPERTY VS_DOTNET_TARGET_FRAMEWORK_VERSION "v4.6.1")
target_link_libraries(TelemetryWsServerCs
StateMachineCs
ConvertersCsInterface
)
set_property(TARGET TelemetryWsServerCs PROPERTY VS_DOTNET_REFERENCES
    "System"
    "System.Net"
    "StateMachineCs"
)