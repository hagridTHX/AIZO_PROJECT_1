#include "Modes.h"
#include <iostream>
#include <cstdlib>
#include <string>

// Definicja funkcji pomocniczej addFolderPrefix w anonimowej przestrzeni nazw
namespace {
    std::string addFolderPrefix(const std::string& filename, const std::string& folder) {
        if (filename.find('/') == std::string::npos && filename.find('\\') == std::string::npos)
            return folder + "/" + filename;
        else
            return filename;
    }
}

BenchmarkMode::BenchmarkMode(int argc, char* argv[])
        : algorithm(0), type(0), pivot(-1), gap(-1), drunk(-1), distribution(-1), runs(-1)
{
    if (argc < 5) {
        std::cerr << "Błąd: Za mało argumentów dla trybu BENCHMARK MODE." << std::endl;
        exit(1);
    }
    // Obowiązkowe argumenty
    algorithm = std::atoi(argv[2]);
    type = std::atoi(argv[3]);
    int currentArg = 4;
    // Parsowanie flag opcjonalnych: --pivot, --gap, --drunk, --distribution, --runs
    while (currentArg < argc && std::string(argv[currentArg]).rfind("--", 0) == 0) {
        std::string flag = argv[currentArg];
        if (flag == "--pivot") {
            if (currentArg + 1 < argc) {
                pivot = std::atoi(argv[currentArg + 1]);
                currentArg += 2;
            } else {
                std::cerr << "Błąd: Brak wartości dla flagi --pivot." << std::endl;
                exit(1);
            }
        } else if (flag == "--gap") {
            if (currentArg + 1 < argc) {
                gap = std::atoi(argv[currentArg + 1]);
                currentArg += 2;
            } else {
                std::cerr << "Błąd: Brak wartości dla flagi --gap." << std::endl;
                exit(1);
            }
        } else if (flag == "--drunk") {
            if (currentArg + 1 < argc) {
                drunk = std::atoi(argv[currentArg + 1]);
                currentArg += 2;
            } else {
                std::cerr << "Błąd: Brak wartości dla flagi --drunk." << std::endl;
                exit(1);
            }
        } else if (flag == "--distribution") {
            if (currentArg + 1 < argc) {
                distribution = std::atoi(argv[currentArg + 1]);
                currentArg += 2;
            } else {
                std::cerr << "Błąd: Brak wartości dla flagi --distribution." << std::endl;
                exit(1);
            }
        } else if (flag == "--runs") {
            if (currentArg + 1 < argc) {
                runs = std::atoi(argv[currentArg + 1]);
                currentArg += 2;
            } else {
                std::cerr << "Błąd: Brak wartości dla flagi --runs." << std::endl;
                exit(1);
            }
        } else {
            break;
        }
    }
    // Opcjonalny argument outputFile
    if (currentArg < argc) {
        std::string rawOutput = argv[currentArg];
        outputFile = addFolderPrefix(rawOutput, "output");
    } else {
        // Jeżeli nie podano outputFile, generujemy nazwę na podstawie wprowadzonych parametrów
        std::string name = "alg" + std::to_string(algorithm) + "_type" + std::to_string(type);
        if (pivot != -1)
            name += "_pivot" + std::to_string(pivot);
        if (gap != -1)
            name += "_gap" + std::to_string(gap);
        if (drunk != -1)
            name += "_drunk" + std::to_string(drunk);
        if (distribution != -1)
            name += "_dist" + std::to_string(distribution);
        if (runs != -1)
            name += "_runs" + std::to_string(runs);
        name += ".txt";
        outputFile = addFolderPrefix(name, "output");
    }
}

void BenchmarkMode::run() {
    std::cout << "Uruchomienie Benchmark Mode:" << std::endl;
    std::cout << "Algorithm: " << algorithm << std::endl;
    std::cout << "Type: " << type << std::endl;
    if (pivot != -1)
        std::cout << "Pivot: " << pivot << std::endl;
    if (gap != -1)
        std::cout << "Gap: " << gap << std::endl;
    if (drunk != -1)
        std::cout << "Drunk: " << drunk << std::endl;
    if (distribution != -1)
        std::cout << "Distribution: " << distribution << std::endl;
    if (runs != -1)
        std::cout << "Runs: " << runs << std::endl;
    std::cout << "Output File: " << outputFile << std::endl;



}
