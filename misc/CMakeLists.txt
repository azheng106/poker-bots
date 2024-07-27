cmake_minimum_required(VERSION 3.28)
project(poker_bots LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(poker_bots
        ../game/Card.cpp
        ../game/Card.h
        ../game/Player.cpp
        ../game/Player.h
        ../main.cpp
        ../game/Game.cpp
        ../game/Game.h
        ../game/CardUtil.cpp
        ../game/CardUtil.h
        ../gui/RecButton.cpp
        ../gui/RecButton.h
        ../gui/Misc.cpp
        ../gui/Misc.h
        ../gui/TriButton.h
        ../gui/TriButton.cpp
        ../gui/Text.h
        ../gui/Text.cpp
)
target_link_libraries(poker_bots PRIVATE sfml-graphics)
target_compile_features(poker_bots PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
            TARGET poker_bots
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:poker_bots>
            VERBATIM)
endif()