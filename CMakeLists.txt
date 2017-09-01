cmake_minimum_required(VERSION 3.8)
project(pong)

set(CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14") # enable C++11 standard

set(SOURCE_FILES
        ball.cpp
        ball.h
        collision.cpp
        collision.h
        constants.h
        font_renderer.cpp
        font_renderer.h
        game.cpp
        paddle.cpp
        paddle.h
        texture.cpp
        texture.h
        texture_pack.cpp
        texture_pack.h
        utilities.cpp
        utilities.h)

add_executable(pong ${SOURCE_FILES})