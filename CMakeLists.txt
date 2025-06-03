cmake_minimum_required(VERSION 3.30)
project(projektAizo LANGUAGES CXX)

# ustawienia C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ostrzeżenia kompilatora
add_compile_options(-Wall -Wextra -Wpedantic -Wshadow -Wconversion)

# opcje w zależności od trybu builda
if(CMAKE_BUILD_TYPE MATCHES Debug)
    message(STATUS "Kompilacja w trybie Debug")
    add_compile_options(-g)
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    message(STATUS "Kompilacja w trybie Release")
    add_compile_options(-O2)
endif()

# statyczne linkowanie na Windowsie
if(WIN32)
    message(STATUS "Włączone statyczne linkowanie na Windowsie (MinGW)")
    set(CMAKE_EXE_LINKER_FLAGS
            "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++ -pthread")
endif()

# tworzenie pliku wykonywalnego (tylko pliki z „Projekt 2”)
add_executable(projektAizo
        main.cpp

        # Timer (tylko jeden raz)
        Timer.cpp
        Timer.h

        # Projekt 2: utils
        "Projekt 2/utils/Modes.h"
        "Projekt 2/utils/FileTestMode.cpp"
        "Projekt 2/utils/BenchmarkMode.cpp"
        "Timer.cpp"
        "Timer.h"

        # Projekt 2: algorytmy grafowe
        "Projekt 2/algorithms/MST.h"
        "Projekt 2/algorithms/MaxFlow.h"
        "Projekt 2/algorithms/ShortestPath.h"

        # Projekt 2: DataGenerator / DataHandler
        "Projekt 2/utils/DataGenerator.h"
        "Projekt 2/utils/DataHandler.h"

        # Jeżeli korzystasz też z BoardGame itp. z Projekt 1, zostaw je, ale nie dubluj FileTestMode/BenchmarkMode:
        "Projekt 1/BoardGame.cpp"
        "Projekt 1/BoardGame.h"
        "Projekt 1/utils/Modes.h"

        # Sortowanie z Projekt 1, jeśli potrzebne
        "Projekt 1/algorithms/SortingAlgorithms.h"
        "Projekt 1/utils/DataGenerator.h"
        "Projekt 1/utils/DataHandler.h"
        "Projekt 2/utils/Edge.h"
        "Projekt 2/utils/GraphStructure.h"
)

# Upewnij się, że nie ma już tych samych plików z Projekt 1 i Projekt 2
# w jednej sekcji add_executable – każdy plik powinien się pojawić tylko raz.
