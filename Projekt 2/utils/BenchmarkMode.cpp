#include "Modes.h"
#include "../algorithms/MST.h"
#include "../algorithms/MaxFlow.h"
#include "../algorithms/ShortestPath.h"
#include "Timer.h"
#include "DataHandler.h"
#include "DataGenerator.h"
#include <iostream>
#include <stdexcept>
#include <string>

BenchmarkMode::BenchmarkMode(int argc, char* argv[]) {
    if (argc < 9) {
        std::cerr << "Błąd: Za mało argumentów dla trybu BENCHMARK MODE.\n";
        exit(1);
    }

    problem = parseInt(argv[2], "<problem>");
    algorithm = parseInt(argv[3], "<algorithm>");
    representation = parseInt(argv[4], "<representation>");
    size = parseInt(argv[5], "<size>");
    density = parseInt(argv[6], "<density>");
    runs = parseInt(argv[7], "<runs>");
    inputFile = addFolderPrefix(argv[8], "input");

    int currentArg = 9;
    while (currentArg < argc) {
        std::string flag = argv[currentArg];
        if (flag == "--start") {
            if (currentArg + 1 < argc) {
                startVertex = parseInt(argv[currentArg + 1], "--start");
                currentArg += 2;
            } else {
                std::cerr << "Błąd: Brak wartości dla flagi --start.\n";
                exit(1);
            }
        } else if (flag == "--end") {
            if (currentArg + 1 < argc) {
                endVertex = parseInt(argv[currentArg + 1], "--end");
                currentArg += 2;
            } else {
                std::cerr << "Błąd: Brak wartości dla flagi --end.\n";
                exit(1);
            }
        } else {
            if (outputFile.empty()) {
                outputFile = addFolderPrefix(flag, "output");
                ++currentArg;
            } else {
                std::cerr << "Błąd: Niezrozumiały dodatkowy argument: " << flag << "\n";
                exit(1);
            }
        }
    }

    if (outputFile.empty()) {
        outputFile = addFolderPrefix("benchmark_result.txt", "output");
    }
}

void BenchmarkMode::run() {
    std::cout << "Rozpoczynanie benchmarku grafowego:\n";
    std::cout << "Problem: " << problem << ", Algorytm: " << algorithm << ", Reprezentacja: " << representation << "\n";
    std::cout << "Liczba wierzchołków: " << size << ", Gęstość: " << density << "%" << ", Powtórzenia: " << runs << "\n";

    int* times = new int[runs];

    for (int i = 0; i < runs; ++i) {
        auto graph = DataGenerator::generateGraph(size, density, representation);

        Timer timer;
        int time = 0;

        switch (problem) {
            case 0: // MST
                time = MST::run(graph, algorithm);
                break;
            case 1: // Shortest Path
                if (startVertex == -1 || endVertex == -1) {
                    std::cerr << "Brak wierzchołków start/end dla najkrótszej ścieżki.\n";
                    delete[] times;
                    exit(1);
                }
                time = ShortestPath::run(graph, algorithm, startVertex, endVertex);
                break;
            case 2: // Max Flow
                time = MaxFlow::run(graph, algorithm);
                break;
            default:
                std::cerr << "Nieznany problem.\n";
                delete[] times;
                exit(1);
        }

        times[i] = timer.elapsedMilliseconds();
    }

    DataHandler handler(outputFile);
    handler.writeGraphBenchmarkResult(problem, algorithm, representation, size, density, runs, times);

    delete[] times;
}

int BenchmarkMode::parseInt(const char* s, const std::string& flagName) {
    try {
        return std::stoi(s);
    } catch (...) {
        std::cerr << "Błąd: Niepoprawna wartość dla " << flagName << ".\n";
        exit(1);
    }
}

std::string BenchmarkMode::addFolderPrefix(const std::string& filename, const std::string& folder) {
    return (filename.find('/') == std::string::npos && filename.find('\\') == std::string::npos)
           ? folder + "/" + filename
           : filename;
}