cmake_minimum_required(VERSION 3.28)
project(PokerBots)

set(CMAKE_CXX_STANDARD 17)

add_executable(PokerBots ../main.cpp
        ../classes/Player.cpp
        ../classes/Player.h
        ../classes/Card.cpp
        ../classes/Util.cpp
        ../classes/Util.h)