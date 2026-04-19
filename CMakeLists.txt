cmake_minimum_required(VERSION 3.20)

project(ProtocolDispatcher LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(ProtocolDispatcher STATIC
    src/core/Dispatcher.cpp
    src/core/HandlerRegistry.cpp
    src/common/Config.cpp
    src/common/Error.cpp
    src/protocols/http/HttpHandler.cpp
    src/protocols/http/HttpValidator.cpp
    src/protocols/websocket/WebSocketHandler.cpp
    src/protocols/websocket/WebSocketSession.cpp
    src/protocols/websocket/WebSocketValidator.cpp
    src/transport/BeastHttpAdapter.cpp
    src/transport/BeastWebSocketAdapter.cpp
)

target_include_directories(ProtocolDispatcher
    PUBLIC
        include
)

