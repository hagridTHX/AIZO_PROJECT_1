cmake_minimum_required(VERSION 3.30)
project(projektAizo)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-Wall -Wextra -Wpedantic -Wshadow -Wconversion)

# Włącz AddressSanitizer tylko na Linuxie
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang" AND NOT MINGW)
    message(STATUS "Używanie AddressSanitizer dla debugowania")
    add_compile_options(-fsanitize=address -g)
    add_link_options(-fsanitize=address)
endif()

if(MINGW)
    message(STATUS "Włączone statyczne linkowanie na MinGW")
    set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++ -pthread")
endif()

# Tworzenie pliku wynikowego
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
