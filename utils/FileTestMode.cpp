#include "Modes.h"
#include <iostream>
#include <stdexcept>
#include <string>

namespace {
    // Funkcja pomocnicza dodająca prefiks folderu, jeśli nazwa pliku nie zawiera ścieżki.
    std::string addFolderPrefix(const std::string& filename, const std::string& folder) {
        if (filename.find('/') == std::string::npos && filename.find('\\') == std::string::npos)
            return folder + "/" + filename;
        else
            return filename;
    }

    // Funkcja pomocnicza do bezpiecznego parsowania liczby całkowitej
    int parseInt(const char* s, const std::string& flagName) {
        try {
            return std::stoi(s);
        } catch (const std::invalid_argument&) {
            std::cerr << "Błąd: Wartość dla " << flagName << " musi być liczbą całkowitą.\n";
            exit(1);
        } catch (const std::out_of_range&) {
            std::cerr << "Błąd: Liczba dla " << flagName << " jest poza zakresem.\n";
            exit(1);
        }
    }
}

FileTestMode::FileTestMode(int argc, char* argv[])
        : algorithm(0), type(0), pivot(-1), gap(-1), drunk(-1)
{
    if (argc < 5) {
        std::cerr << "Błąd: Za mało argumentów dla trybu FILE TEST MODE." << std::endl;
        exit(1);
    }
    // Parsowanie obowiązkowych argumentów
    algorithm = parseInt(argv[2], "<algorithm>");
    type = parseInt(argv[3], "<type>");
    int currentArg = 4;

    // Parsowanie flag opcjonalnych: --pivot, --gap, --drunk
    while (currentArg < argc && std::string(argv[currentArg]).rfind("--", 0) == 0) {
        std::string flag = argv[currentArg];
        if (flag == "--pivot") {
            if (currentArg + 1 < argc) {
                pivot = parseInt(argv[currentArg + 1], "--pivot");
                currentArg += 2;
            } else {
                std::cerr << "Błąd: Brak wartości dla flagi --pivot." << std::endl;
                exit(1);
            }
        } else if (flag == "--gap") {
            if (currentArg + 1 < argc) {
                gap = parseInt(argv[currentArg + 1], "--gap");
                currentArg += 2;
            } else {
                std::cerr << "Błąd: Brak wartości dla flagi --gap." << std::endl;
                exit(1);
            }
        } else if (flag == "--drunk") {
            if (currentArg + 1 < argc) {
                drunk = parseInt(argv[currentArg + 1], "--drunk");
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

    // Opcjonalny argument outputFile; jeżeli nie podano, ustawiamy na [inputFile]OUT.txt
    if (currentArg < argc) {
        std::string rawOutput = argv[currentArg];
        outputFile = addFolderPrefix(rawOutput, "output");
    } else {
        outputFile = inputFile + "OUT.txt";
        // Można dodatkowo dodać prefiks folderu, jeśli chcesz, np.:
        // outputFile = addFolderPrefix(outputFile, "output");
    }
}

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

    // TODO: Dodaj kod wywołujący sortowanie i zapis wyników pomiarów.
}
