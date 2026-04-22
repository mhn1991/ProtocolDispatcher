cmake_minimum_required(VERSION 3.20)

project(ProtocolDispatcher LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)

add_library(ProtocolDispatcher STATIC
    src/core/Dispatcher.cpp
    src/core/HandlerRegistry.cpp
    src/common/Config.cpp
    src/common/Error.cpp
    src/net/Resolver.cpp
    src/net/Socket.cpp
    src/net/TcpClient.cpp
    src/protocols/http/HttpClient.cpp
    src/protocols/http/HttpHandler.cpp
    src/protocols/http/HttpParser.cpp
    src/protocols/http/HttpSerializer.cpp
    src/protocols/http/HttpValidator.cpp
    src/protocols/websocket/WebSocketHandler.cpp
    src/protocols/websocket/WebSocketSession.cpp
    src/protocols/websocket/WebSocketValidator.cpp
)

target_include_directories(ProtocolDispatcher
    PUBLIC
        include
)

if(BUILD_TESTING)
    include(FetchContent)

    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    )

    FetchContent_MakeAvailable(googletest)
endif()
