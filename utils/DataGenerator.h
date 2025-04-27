#ifndef PROJEKTAIZO_DATAGENERATOR_H
#define PROJEKTAIZO_DATAGENERATOR_H

#include <random>
#include <algorithm>
#include <type_traits>
#include <limits>
#include "../BoardGame.h"

class DataGenerator {
private:
    int distribution;
    int size;
    std::mt19937 rng;

public:
    DataGenerator(int _distribution, int _size)
            : distribution(_distribution), size(_size), rng(std::random_device{}()) {}

    ~DataGenerator() = default;

    template<typename T>
    void partialSort(T* data, int n, int nominator) {
        int count = n / 3 * nominator;
        if (count > 0 && count <= n) {
            std::sort(data, data + count);
        }
    }

    template<typename T>
    T generateRandomValue();

    template<typename T>
    T* generateData() {
        T* data = new T[size];
        for (int i = 0; i < size; ++i) {
            data[i] = generateRandomValue<T>();
        }
        switch (distribution) {
            case 1:
                std::sort(data, data + size);
                break;
            case 2:
                std::sort(data, data + size, std::greater<>());
                break;
            case 3:
                partialSort(data, size, 1);
                break;
            case 4:
                partialSort(data, size, 2);
                break;
            default:
                break;
        }
        return data;
    }

private:
    std::mt19937& getRng() {
        return rng;
    }
};

template<typename T>
T DataGenerator::generateRandomValue() {
    if constexpr (std::is_same_v<T, char>) {
        std::uniform_int_distribution<int> dist(0, 255);
        return static_cast<char>(dist(getRng()));
    } else if constexpr (std::is_integral_v<T>) {
        std::uniform_int_distribution<T> dist(
                std::numeric_limits<T>::min(),
                std::numeric_limits<T>::max()
        );
        return dist(getRng());
    } else if constexpr (std::is_floating_point_v<T>) {
        std::uniform_real_distribution<T> dist(
                std::numeric_limits<T>::lowest(),
                std::numeric_limits<T>::max()
        );
        return dist(getRng());
    } else {
        static_assert(std::is_arithmetic_v<T>, "Nieobsługiwany typ w generateRandomValue");
    }
}

template<>
inline BoardGame DataGenerator::generateRandomValue<BoardGame>() {
    char name[26], publisher[26];
    std::uniform_int_distribution<int> letterDist('A', 'Z');
    std::uniform_int_distribution<int> letterDistLower('a', 'z');
    std::uniform_int_distribution<int> lengthDist(3, 25);

    int nameLen = lengthDist(getRng());
    int pubLen = lengthDist(getRng());
    for (int i = 0; i < nameLen; ++i) name[i] = static_cast<char>(letterDist(getRng()));
    name[nameLen] = '\0';
    for (int i = 0; i < pubLen; ++i) publisher[i] = static_cast<char>(letterDistLower(getRng()));
    publisher[pubLen] = '\0';

    std::uniform_int_distribution<int> minPlayerDist(1, 10);
    std::uniform_int_distribution<int> maxPlayerDist(1, 10);
    std::uniform_int_distribution<int> durationDist(5, 480);
    std::uniform_int_distribution<int> levelDist(1, 10);

    int minP = minPlayerDist(getRng());
    int maxP = std::max(minP, maxPlayerDist(getRng()));
    int dur = durationDist(getRng());
    int complexity = levelDist(getRng());
    int joy = levelDist(getRng());

    return {name, publisher, minP, maxP, dur, complexity, joy};
}

#endif // PROJEKTAIZO_DATAGENERATOR_H
