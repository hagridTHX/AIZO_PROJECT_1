#ifndef PROJEKTAIZO_DATA_H
#define PROJEKTAIZO_DATA_H

#include <string>
#include <type_traits>
#include <limits>
#include <fstream>
#include <random>
#include <algorithm>
#include "../BoardGame.h"

class DataGenerator {
public:
    // Częściowe sortowanie: nominator to wielokrotność 1/3 rozmiaru
    template<typename T>
    static void partialSort(T* data, int n, int nominator);

    // Dostęp do generatora liczb losowych
    static std::mt19937& getRng();

    // Generacja losowej wartości typu T (w .cpp będzie też specjalizacja dla BoardGame)
    template<typename T>
    static T generateRandomValue();

    // Generacja tablicy danych z określonym rozkładem
    template<typename T>
    static T* generateData(int n, int distType);
};

class DataHandler {
public:
    // Odczyt z pliku: pierwszy wiersz to rozmiar, potem wartości
    template<typename T>
    static T* readFromFile(const std::string& filename, int& size);

    // Zapis do pliku: pierwszy wiersz to rozmiar, potem wartości
    template<typename T>
    static void writeToFile(const std::string& filename, T* data, int size);
};

#endif
