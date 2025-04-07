#include "Data.h"
#include <algorithm>
#include <random>
#include <functional>
#include <limits>

namespace {

    template <typename T>
    void partialSort(T* data, int n, int nominator) {
        int count = n / 3;
        count = count * nominator;
        if (count > 0 && count <= n) {
            std::sort(data, data + count);
        }
    }

    // generator liczb losowych.
    std::mt19937 create_rng() {
        static std::random_device rd;
        return std::mt19937(rd());
    }
}

int* DataGenerator::generateIntData(int n, int distType) {
    int* data = new int[n];
    auto rng = create_rng();

    // Generujemy wartości z pełnego zakresu typu int.
    std::uniform_int_distribution<int> dist(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
    for (int i = 0; i < n; ++i) {
        data[i] = dist(rng);
    }

    switch (distType) {
        case 1:
            std::sort(data, data + n);
            break;
        case 2:
            std::sort(data, data + n, std::greater<>());
            break;
        case 3:
            partialSort(data, n, 1); // sortujemy pierwszą 1/3 tablicy
            break;
        case 4:
            partialSort(data, n, 2); // sortujemy pierwsze 2/3 tablicy
            break;
        default:
            // 0 – brak sortowania (losowy)
            break;
    }
    return data;
}

float* DataGenerator::generateFloatData(int n, int distType) {
    float* data = new float[n];
    auto rng = create_rng();

    std::uniform_real_distribution<float> dist(std::numeric_limits<float>::lowest(), std::numeric_limits<float>::max());
    for (int i = 0; i < n; ++i) {
        data[i] = dist(rng);
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

char* DataGenerator::generateCharData(int n, int distType) {
    char* data = new char[n];
    auto rng = create_rng();

    std::uniform_int_distribution<int> dist(std::numeric_limits<char>::min(), std::numeric_limits<char>::max());
    for (int i = 0; i < n; ++i) {
        data[i] = static_cast<char>(dist(rng));
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
