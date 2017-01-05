cmake_minimum_required(VERSION 3.3)
project(Game)

find_package(Boost REQUIRED COMPONENTS system)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lboost_system -lpthread")

set(SOURCE_FILES
    Game.cpp
    Game.h
    main.cpp
    Player.cpp
    Player.h
    RandomNumberGenerator.cpp
    RandomNumberGenerator.h
    WebsocketServer.cpp
    WebsocketServer.h
    PlayerMovementSubjectObserver.cpp
    PlayerMovementSubjectObserver.h
    Types.h)

include_directories(dependencies/websocketpp)

add_executable(Game ${SOURCE_FILES})