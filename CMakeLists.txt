cmake_minimum_required(VERSION 3.30)
project(projektAizo)

set(CMAKE_CXX_STANDARD 20)

add_executable(projektAizo main.cpp
        utils/Timer.cpp
        utils/Timer.h
        utils/DataHandler.cpp
        BoardGame.cpp
        BoardGame.h
        utils/DataGenerator.cpp
        utils/Modes.h
        utils/Data.h
        utils/FileTestMode.cpp
        utils/BenchmarkMode.cpp
        algorithms/SortingAlgorithms.cpp
        algorithms/SortingAlgorithms.h
)
