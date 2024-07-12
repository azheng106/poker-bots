cmake_minimum_required(VERSION 3.28)
project(PokerBots)

set(CMAKE_CXX_STANDARD 17)

add_executable(PokerBots main.cpp
        Player.cpp
        Player.h
        Card.cpp
        Util.cpp
        Util.h)
