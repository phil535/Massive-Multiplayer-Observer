cmake_minimum_required(VERSION 3.3)
project(Game)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unused-parameter -std=c++11 -lboost_system -pthread")

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
    Types.h
    MovementPattern.cpp
    MovementPattern.h)

include_directories(dependencies/websocketpp)

find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
add_executable(Game ${SOURCE_FILES})
target_link_libraries(Game ${Boost_LIBRARIES})