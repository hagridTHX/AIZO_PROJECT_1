#include "Modes.h"
#include "../algorithms/SortingAlgorithms.h"
#include "DataHandler.h"
#include "Timer.h"
#include <iostream>
#include <stdexcept>
#include <filesystem>

FileTestMode::FileTestMode(int argc, char* argv[])
        : algorithm(-1), type(-1), pivot(-1), gap(-1), drunk(-1)
{
    if (argc < 5) {
        std::cerr << "Błąd: Za mało argumentów dla trybu FILE TEST MODE.\n";
        exit(1);
    }

    algorithm = parseInt(argv[2], "<algorithm>");
    type = parseInt(argv[3], "<type>");
    int currentArg = 4;

    if (currentArg >= argc) {
        std::cerr << "Błąd: Brak inputFile.\n";
        exit(1);
    }

    inputFile = addFolderPrefix(argv[currentArg++], "input");

    // Jeśli jest kolejny argument i nie zaczyna się od '--', to jest to outputFile
    if (currentArg < argc && argv[currentArg][0] != '-') {
        outputFile = addFolderPrefix(argv[currentArg++], "output");
    } else {
        // Domyślna nazwa outputFile
        std::string inputFilenameOnly = std::filesystem::path(inputFile).filename().string();
        size_t dotPos = inputFilenameOnly.rfind('.');
        if (dotPos != std::string::npos) {
            inputFilenameOnly.insert(dotPos, "OUT");
        } else {
            inputFilenameOnly += "OUT";
        }
        outputFile = addFolderPrefix(inputFilenameOnly, "output");
    }

    // Teraz dopiero parsujemy flagi (--pivot, --gap, --drunk)
    while (currentArg < argc) {
        std::string flag = argv[currentArg];

        if (flag == "--pivot") {
            if (currentArg + 1 < argc) {
                pivot = parseInt(argv[currentArg + 1], "--pivot");
                currentArg += 2;
            } else {
                std::cerr << "Błąd: Brak wartości dla flagi --pivot.\n";
                exit(1);
            }
        } else if (flag == "--gap") {
            if (currentArg + 1 < argc) {
                gap = parseInt(argv[currentArg + 1], "--gap");
                currentArg += 2;
            } else {
                std::cerr << "Błąd: Brak wartości dla flagi --gap.\n";
                exit(1);
            }
        } else if (flag == "--drunk") {
            if (currentArg + 1 < argc) {
                drunk = parseInt(argv[currentArg + 1], "--drunk");
                currentArg += 2;
            } else {
                std::cerr << "Błąd: Brak wartości dla flagi --drunk.\n";
                exit(1);
            }
        } else {
            std::cerr << "Błąd: Nieznana flaga lub parametr: " << flag << "\n";
            exit(1);
        }
    }
}

void FileTestMode::run() {
    std::cout << "Uruchamianie File Test Mode:\n";
    std::cout << "Algorithm: " << algorithm << "\n";
    std::cout << "Type: " << type << "\n";
    if (pivot != -1) std::cout << "Pivot: " << pivot << "\n";
    if (gap != -1) std::cout << "Gap: " << gap << "\n";
    if (drunk != -1) std::cout << "Drunk: " << drunk << "\n";
    std::cout << "Input File: " << inputFile << "\n";
    std::cout << "Output File: " << outputFile << "\n";

    Timer timer;
    DataHandler handler(inputFile, outputFile);

    if (type == 0) {
        int* data = handler.readFromFile<int>();
        SortingAlgorithms<int> sorter(data, algorithm, handler.getSize(), pivot, gap, drunk);

        timer.reset();
        timer.start();
        sorter.sort(timer);
        timer.stop();

        if (algorithm == 4) {
            int retries = 0;
            while (!sorter.isSorted()) {
                ++retries;
                sorter.decrDrunk();
                std::cout << "[!] Retry #" << retries << "\n";
                Timer retryTimer;
                sorter.sort(retryTimer);
            }
        } else {
            if (!sorter.isSorted()) {
                std::cerr << "[!] Błąd: Algorytm " << algorithm << " nie posortował poprawnie danych.\n";
                delete[] data;
                exit(1);
            }
        }

        handler.writeToFile(data, handler.getSize());
        delete[] data;

    } else if (type == 1) {
        float* data = handler.readFromFile<float>();
        SortingAlgorithms<float> sorter(data, algorithm, handler.getSize(), pivot, gap, drunk);

        timer.reset();
        timer.start();
        sorter.sort(timer);
        timer.stop();

        if (algorithm == 4) {
            int retries = 0;
            while (!sorter.isSorted()) {
                ++retries;
                sorter.decrDrunk();
                std::cout << "[!] Retry #" << retries << "\n";
                Timer retryTimer;
                sorter.sort(retryTimer);
            }
        } else {
            if (!sorter.isSorted()) {
                std::cerr << "[!] Błąd: Algorytm " << algorithm << " nie posortował poprawnie danych.\n";
                delete[] data;
                exit(1);
            }
        }

        handler.writeToFile(data, handler.getSize());
        delete[] data;

    } else if (type == 2) {
        char* data = handler.readFromFile<char>();
        SortingAlgorithms<char> sorter(data, algorithm, handler.getSize(), pivot, gap, drunk);

        timer.reset();
        timer.start();
        sorter.sort(timer);
        timer.stop();

        if (algorithm == 4) {
            int retries = 0;
            while (!sorter.isSorted()) {
                ++retries;
                sorter.decrDrunk();
                std::cout << "[!] Retry #" << retries << "\n";
                Timer retryTimer;
                sorter.sort(retryTimer);
            }
        } else {
            if (!sorter.isSorted()) {
                std::cerr << "[!] Błąd: Algorytm " << algorithm << " nie posortował poprawnie danych.\n";
                delete[] data;
                exit(1);
            }
        }

        handler.writeToFile(data, handler.getSize());
        delete[] data;

    } else if (type == 3) {
        BoardGame* data = handler.readFromFile<BoardGame>();
        SortingAlgorithms<BoardGame> sorter(data, algorithm, handler.getSize(), pivot, gap, drunk);

        timer.reset();
        timer.start();
        sorter.sort(timer);
        timer.stop();

        if (algorithm == 4) {
            int retries = 0;
            while (!sorter.isSorted()) {
                ++retries;
                sorter.decrDrunk();
                std::cout << "[!] Retry #" << retries << "\n";
                Timer retryTimer;
                sorter.sort(retryTimer);
            }
        } else {
            if (!sorter.isSorted()) {
                std::cerr << "[!] Błąd: Algorytm " << algorithm << " nie posortował poprawnie danych.\n";
                delete[] data;
                exit(1);
            }
        }

        handler.writeToFile(data, handler.getSize());
        delete[] data;

    } else {
        std::cerr << "Błąd: Nieznany typ danych.\n";
        exit(1);
    }
}


int FileTestMode::parseInt(const char* s, const std::string& flagName) {
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

std::string FileTestMode::addFolderPrefix(const std::string& filename, const std::string& folder) {
    if (filename.find('/') == std::string::npos && filename.find('\\') == std::string::npos)
        return folder + "/" + filename;
    else
        return filename;
}