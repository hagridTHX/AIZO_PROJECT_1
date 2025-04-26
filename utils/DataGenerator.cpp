#include <type_traits>
#include <algorithm>
#include <random>
#include <functional>
#include <limits>
#include "../BoardGame.h"
#include "Data.h"

template<typename T>
void DataGenerator::partialSort(T* data, int n, int nominator) {
    int count = n / 3 * nominator;
    if (count > 0 && count <= n) {
        std::sort(data, data + count);
    }
}

// getRng
std::mt19937& DataGenerator::getRng() {
    static std::random_device rd;
    static std::mt19937 rng(rd());
    return rng;
}

// generateRandomValue - ogólna
template<typename T>
T DataGenerator::generateRandomValue() {
    if constexpr (std::is_same_v<T, char>) {
        std::uniform_int_distribution<int> dist(0, 255);
        return static_cast<char>(dist(getRng()));
    } else if constexpr (std::is_integral_v<T>) {
        std::uniform_int_distribution<T> dist(
                std::numeric_limits<T>::min(),
                std::numeric_limits<T>::max());
        return dist(getRng());
    } else if constexpr (std::is_floating_point_v<T>) {
        std::uniform_real_distribution<T> dist(
                std::numeric_limits<T>::lowest(),
                std::numeric_limits<T>::max());
        return dist(getRng());
    } else {
        static_assert(std::is_arithmetic_v<T>,
                      "nie wspierany typ dla generateRandomValue");
    }
}

template<>
BoardGame DataGenerator::generateRandomValue<BoardGame>() {
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

// generateData
template<typename T>
T* DataGenerator::generateData(int n, int distType) {
    T* data = new T[n];
    for (int i = 0; i < n; ++i) {
        data[i] = generateRandomValue<T>();
    }
    switch (distType) {
        case 1:
            std::sort(data, data + n);
            break;
        case 2:
            std::sort(data, data + n, std::greater<>());
            break;
        case 3:
            partialSort(data, n, 1);
            break;
        case 4:
            partialSort(data, n, 2);
            break;
        default:
            break;
    }
    return data;
}