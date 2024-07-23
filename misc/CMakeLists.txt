cmake_minimum_required(VERSION 3.28)
project(poker_bots)

set(CMAKE_CXX_STANDARD 14)

include_directories("../classes")
include_directories("C:/SFML/lib/cmake/SFML")
include_directories("C:/SFML/include")
link_directories("C:/SFML/lib")

set(SFML_DIR "C:/SFML/lib/cmake/SFML")
find_package(SFML 2.6 COMPONENTS system window graphics network audio REQUIRED)
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

target_link_libraries(poker_bots sfml-graphics sfml-window sfml-system sfml-network sfml-audio)
target_link_libraries(poker_bots
        "C:/SFML/lib/libsfml-graphics.a"
        "C:/SFML/lib/libsfml-window.a"
        "C:/SFML/lib/libsfml-system.a"
        "C:/SFML/lib/libsfml-network.a"
        "C:/SFML/lib/libsfml-audio.a"
)