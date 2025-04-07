#include "Modes.h"
#include <iostream>
#include <stdexcept>
#include <string>

namespace {
    std::string addFolderPrefix(const std::string& filename, const std::string& folder) {
        if (filename.find('/') == std::string::npos && filename.find('\\') == std::string::npos)
            return folder + "/" + filename;
        else
            return filename;
    }


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

BenchmarkMode::BenchmarkMode(int argc, char* argv[])
        : algorithm(0), type(0), pivot(-1), gap(-1), drunk(-1), distribution(-1), runs(-1)
{
    if (argc < 5) {
        std::cerr << "Błąd: Za mało argumentów dla trybu BENCHMARK MODE." << std::endl;
        exit(1);
    }

    algorithm = parseInt(argv[2], "<algorithm>");
    type = parseInt(argv[3], "<type>");
    int currentArg = 4;

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
        } else if (flag == "--distribution") {
            if (currentArg + 1 < argc) {
                distribution = parseInt(argv[currentArg + 1], "--distribution");
                currentArg += 2;
            } else {
                std::cerr << "Błąd: Brak wartości dla flagi --distribution." << std::endl;
                exit(1);
            }
        } else if (flag == "--runs") {
            if (currentArg + 1 < argc) {
                runs = parseInt(argv[currentArg + 1], "--runs");
                currentArg += 2;
            } else {
                std::cerr << "Błąd: Brak wartości dla flagi --runs." << std::endl;
                exit(1);
            }
        } else {
            break;
        }
    }

    if (currentArg < argc) {
        std::string rawOutput = argv[currentArg];
        outputFile = addFolderPrefix(rawOutput, "output");
    } else {

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

    // TODO: kod wywołujący sortowanie i zapis wyników pomiarów.
}
