cmake_minimum_required(VERSION 3.30)
project(projektAizo)

set(CMAKE_CXX_STANDARD 20)

add_executable(projektAizo main.cpp
        utils/Timer.cpp
        utils/Timer.h
        utils/FileHandler.cpp
        utils/FileHandler.h
        BoardGame.cpp
        BoardGame.h)
