#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <type_traits>
#include "../BoardGame.h"
#include "Data.h"

template<typename T>
T* DataHandler::readFromFile(const std::string& filename, int& size) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        throw std::runtime_error("Cannot open input file: " + filename);
    }

    in >> size;
    T* data = new T[size];

    if constexpr (std::is_same_v<T, BoardGame>) {
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        for (int i = 0; i < size; ++i) {
            std::string name, publisher;
            int minP, maxP, dur, complexity, joy;
            in >> name >> publisher >> minP >> maxP >> dur >> complexity >> joy;
            data[i] = BoardGame(name.c_str(), publisher.c_str(), minP, maxP, dur, complexity, joy);
        }
    } else {
        for (int i = 0; i < size; ++i) {
            in >> data[i];
        }
    }

    in.close();
    return data;
}

// Zapis do pliku
template<typename T>
void DataHandler::writeToFile(const std::string& filename, T* data, int size) {
    std::ofstream out(filename);
    if (!out.is_open()) {
        throw std::runtime_error("Cannot open output file: " + filename);
    }

    out << size << '\n';

    if constexpr (std::is_same_v<T, BoardGame>) {
        for (int i = 0; i < size; ++i) {
            out << data[i].getName() << " "
                << data[i].getPublisher() << " "
                << data[i].getMinPlayers() << " "
                << data[i].getMaxPlayers() << " "
                << data[i].getDuration() << " "
                << data[i].getComplexity() << " "
                << data[i].getJoy() << '\n';
        }
    } else {
        for (int i = 0; i < size; ++i) {
            out << data[i] << '\n';
        }
    }

    out.close();
}