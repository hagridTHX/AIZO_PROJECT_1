cmake_minimum_required(VERSION 3.30)
project(projektAizo LANGUAGES CXX)

# ustawienia C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# kompilatorowe opcje ostrzeżeń
add_compile_options(-Wall -Wextra -Wpedantic -Wshadow -Wconversion)

# opcje kompilacji zależne od typu builda (Debug / Release)
if(CMAKE_BUILD_TYPE MATCHES Debug)
    message(STATUS "Kompilacja w trybie Debug")
    add_compile_options(-g)
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    message(STATUS "Kompilacja w trybie Release")
    add_compile_options(-O2)
endif()

# statyczne linkowanie tylko na Windowsie
if(WIN32)
    message(STATUS "Włączone statyczne linkowanie na Windowsie (MinGW)")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++ -pthread")
endif()

# tworzenie pliku wykonywalnego
add_executable(projektAizo
        main.cpp
        utils/Timer.cpp
        utils/Timer.h
        BoardGame.cpp
        BoardGame.h
        utils/Modes.h
        utils/FileTestMode.cpp
        utils/BenchmarkMode.cpp
        algorithms/SortingAlgorithms.h
        utils/DataGenerator.h
        utils/DataHandler.h
)