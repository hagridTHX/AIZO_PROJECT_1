#include "Modes.h"
#include <iostream>
#include <cstdlib>
#include <string>

FileTestMode::FileTestMode(int argc, char* argv[])
        : algorithm(0), type(0), pivot(-1), gap(-1), drunk(-1)
{
    if (argc < 5) {
        std::cerr << "Błąd: Za mało argumentów dla trybu FILE TEST MODE." << std::endl;
        exit(1);
    }
    // Obowiązkowe argumenty
    algorithm = std::atoi(argv[2]);
    type = std::atoi(argv[3]);
    int currentArg = 4;
    // Parsowanie flag opcjonalnych: --pivot, --gap, --drunk
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
        } else {
            std::cerr << "Błąd: Nieznany parametr: " << flag << std::endl;
            exit(1);
        }
    }
    // Kolejny argument musi być inputFile
    if (currentArg >= argc) {
        std::cerr << "Błąd: Brak argumentu inputFile." << std::endl;
        exit(1);
    }
    inputFile = argv[currentArg++];
    // Opcjonalny argument outputFile
    if (currentArg < argc) {
        outputFile = argv[currentArg];
    } else {
        outputFile = inputFile + "OUT.txt";
    }
}

// Metoda wykonująca operacje trybu FILE TEST MODE
void FileTestMode::run() {
    std::cout << "Uruchomienie File Test Mode:" << std::endl;
    std::cout << "Algorithm: " << algorithm << std::endl;
    std::cout << "Type: " << type << std::endl;
    if (pivot != -1)
        std::cout << "Pivot: " << pivot << std::endl;
    if (gap != -1)
        std::cout << "Gap: " << gap << std::endl;
    if (drunk != -1)
        std::cout << "Drunk: " << drunk << std::endl;
    std::cout << "Input File: " << inputFile << std::endl;
    std::cout << "Output File: " << outputFile << std::endl;


}