#ifndef MODES_H
#define MODES_H

#include <string>

class FileTestMode {
public:
    int algorithm;
    int type;
    int pivot;
    int gap;
    int drunk;
    std::string inputFile;
    std::string outputFile;

    // Konstruktor parsujący argumenty dla trybu FILE TEST MODE
    FileTestMode(int argc, char* argv[]);
    // Metoda uruchamiająca operacje trybu FILE TEST MODE (np. sortowanie i zapis wyników)
    void run();
};

class BenchmarkMode {
public:
    int algorithm;
    int type;
    int pivot;
    int gap;
    int drunk;
    int distribution;
    int runs;
    std::string outputFile;

    // Konstruktor parsujący argumenty dla trybu BENCHMARK MODE
    BenchmarkMode(int argc, char* argv[]);
    // Metoda uruchamiająca operacje trybu BENCHMARK MODE (np. generowanie danych, pomiary i zapis wyników)
    void run();
};

#endif // MODES_H
