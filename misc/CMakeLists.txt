cmake_minimum_required(VERSION 3.28)
project(poker_bots)

set(CMAKE_CXX_STANDARD 14)

include_directories(../classes)

add_executable(poker_bots
        ../classes/Card.cpp
        ../classes/Card.h
        ../classes/Player.cpp
        ../classes/Player.h
        ../main.cpp
        ../classes/Game.cpp
        ../classes/Game.h
        ../classes/CardUtil.cpp
        ../classes/CardUtil.h
)
