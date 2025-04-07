#include "Data.h"
#include <algorithm>
#include <random>
#include <functional> // dla std::greater<>

namespace {
    // Funkcja pomocnicza do częściowego sortowania – sortuje pierwsze (n * fraction) elementów
    template <typename T>
    void partialSort(T* data, int n, float fraction) {
        // Używamy static_cast<float>(n) * fraction, aby uniknąć ostrzeżeń
        int count = static_cast<int>(static_cast<float>(n) * fraction);
        if (count > 0 && count <= n) {
            std::sort(data, data + count);
        }
    }

    // Funkcja pomocnicza tworząca i zwracająca gotowy generator liczb losowych
    // bez ostrzeżeń Clang-Tidy (zamiast time(nullptr))
    std::mt19937 create_rng() {
        static std::random_device rd;  // w praktyce można trzymać w static, by nie wywoływać za często
        return std::mt19937(rd());
    }
}

int* DataGenerator::generateIntData(int n, int distType) {
    int* data = new int[n];
    auto rng = create_rng();

    std::uniform_int_distribution<int> dist(-1000, 1000);
    for (int i = 0; i < n; ++i) {
        data[i] = dist(rng);
    }

    switch(distType) {
        case 1:
            std::sort(data, data + n);
            break;
        case 2:
            std::sort(data, data + n, std::greater<>()); // transparent functor
            break;
        case 3:
            partialSort(data, n, 0.33F);
            break;
        case 4:
            partialSort(data, n, 0.66F);
            break;
        default:
            // 0 - brak sortowania (losowy)
            break;
    }
    return data;
}

float* DataGenerator::generateFloatData(int n, int distType) {
    auto* data = new float[n];
    auto rng = create_rng();

    std::uniform_real_distribution<float> dist(-1000.0F, 1000.0F);
    for (int i = 0; i < n; ++i) {
        data[i] = dist(rng);
    }

    switch(distType) {
        case 1:
            std::sort(data, data + n);
            break;
        case 2:
            std::sort(data, data + n, std::greater<>());
            break;
        case 3:
            partialSort(data, n, 0.33F);
            break;
        case 4:
            partialSort(data, n, 0.66F);
            break;
        default:
            break;
    }
    return data;
}

char* DataGenerator::generateCharData(int n, int distType) {
    char* data = new char[n];
    auto rng = create_rng();

    std::uniform_int_distribution<int> dist('a', 'z');
    for (int i = 0; i < n; ++i) {
        data[i] = static_cast<char>(dist(rng));
    }

    switch(distType) {
        case 1:
            std::sort(data, data + n);
            break;
        case 2:
            std::sort(data, data + n, std::greater<>());
            break;
        case 3:
            partialSort(data, n, 0.33F);
            break;
        case 4:
            partialSort(data, n, 0.66F);
            break;
        default:
            break;
    }
    return data;
}
