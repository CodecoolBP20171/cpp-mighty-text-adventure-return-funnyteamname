cmake_minimum_required(VERSION 3.8)
project(Mighty_text_adventure)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Area.hpp
        Enemy.cpp
        Enemy.h
        Game.cpp
        Game.h
        Item.cpp
        Item.h
        main.cpp
        Player.cpp
        Player.h
        Zone.cpp
        Zone.h)

add_executable(Mighty_text_adventure ${SOURCE_FILES})