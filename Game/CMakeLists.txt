cmake_minimum_required(VERSION 3.3)
project(Game)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lboost_system -lpthread")

set(SOURCE_FILES
    Game.cpp
    Game.h
    main.cpp
    Player.cpp
    Player.h
    Position.cpp
    Position.h
    RandomNumberGenerator.cpp
    RandomNumberGenerator.h
    WebsocketServer.cpp
    WebsocketServer.h)

include_directories(../websocketpp)

add_executable(Game ${SOURCE_FILES})