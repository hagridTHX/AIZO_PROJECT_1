#include "Modes.h"
#include "../algorithms/SortingAlgorithms.h"
#include "../../Timer.h"
#include "../BoardGame.h"
#include "DataHandler.h"
#include "DataGenerator.h"
#include <iostream>
#include <stdexcept>
#include <string>

BenchmarkMode::BenchmarkMode(int argc, char* argv[])
        : algorithm(-1), type(-1), size(-1), pivot(-1), gap(-1), drunk(-1), distribution(-1), runs(-1)
{
    if (argc < 7) {
        std::cerr << "Błąd: Za mało argumentów dla trybu BENCHMARK MODE.\n";
        exit(1);
    }

    for (int i = 0; i < argc; ++i) {
        std::cout << argv[i] << " ";
    }
    std::cout << "\n";

    algorithm = parseInt(argv[2], "<algorithm>");
    type = parseInt(argv[3], "<type>");
    size = parseInt(argv[4], "<size>");
    runs = parseInt(argv[5], "<runs>");
    distribution = parseInt(argv[6], "<distribution>");

    int currentArg = 7;

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
            if (outputFile.empty()) {
                outputFile = addFolderPrefix(argv[currentArg], "output");
                ++currentArg;
            } else {
                std::cerr << "Błąd: Niezrozumiały dodatkowy argument: " << argv[currentArg] << "\n";
                exit(1);
            }
        }
    }

    if (outputFile.empty()) {
        std::string name = "alg" + std::to_string(algorithm) +
                           "_type" + std::to_string(type) +
                           "_size" + std::to_string(size) +
                           "_runs" + std::to_string(runs);

        if (pivot != -1) name += "_pivot" + std::to_string(pivot);
        if (gap != -1) name += "_gap" + std::to_string(gap);
        if (drunk != -1) name += "_drunk" + std::to_string(drunk);
        if (distribution != -1) name += "_dist" + std::to_string(distribution);

        name += ".txt";
        outputFile = addFolderPrefix(name, "output");
    }
}

void BenchmarkMode::run() {
    std::cout << "Uruchamianie Benchmark Mode:\n";
    std::cout << "Algorithm: " << algorithm << "\n";
    std::cout << "Type: " << type << "\n";
    std::cout << "Size: " << size << "\n";
    std::cout << "Runs: " << runs << "\n";
    if (pivot != -1) std::cout << "Pivot: " << pivot << "\n";
    if (gap != -1) std::cout << "Gap: " << gap << "\n";
    if (drunk != -1) std::cout << "Drunk: " << drunk << "\n";
    if (distribution != -1) std::cout << "Distribution: " << distribution << "\n";
    std::cout << "Output file: " << outputFile << "\n";

    int* times = new int[runs];
    int retries;

    for (int i = 0; i < runs; ++i) {
        DataGenerator generator(distribution, size);

        retries = 0;

        if (type == 0) {
            int* data = generator.generateData<int>();
            SortingAlgorithms<int> sorter(data, algorithm, size, pivot, gap, drunk);

            Timer timer;
            times[i] = sorter.sort(timer);

            if (algorithm == 4) {
                while (!sorter.isSorted()) {
                    ++retries;
                    sorter.decrDrunk();
                    std::cout << "[!] Retry #" << retries << " for attempt " << (i + 1) << " " << drunk << "\n";
                    Timer retryTimer;
                    times[i] += sorter.sort(retryTimer);
                }
            } else {
                if (!sorter.isSorted()) {
                    std::cerr << "[!] Błąd: Algorytm " << algorithm << " nie posortował poprawnie danych (run #" << (i + 1) << ").\n";
                    delete[] data;
                    delete[] times;
                    exit(1);
                }
            }
            delete[] data;

        } else if (type == 1) {
            float* data = generator.generateData<float>();
            SortingAlgorithms<float> sorter(data, algorithm, size, pivot, gap, drunk);

            Timer timer;
            times[i] = sorter.sort(timer);

            if (algorithm == 4) {
                while (!sorter.isSorted()) {
                    ++retries;
                    sorter.decrDrunk();
                    std::cout << "[!] Retry #" << retries << " for attempt " << (i + 1) << " " << drunk << "\n";
                    Timer retryTimer;
                    times[i] += sorter.sort(retryTimer);
                }
            } else {
                if (!sorter.isSorted()) {
                    std::cerr << "[!] Błąd: Algorytm " << algorithm << " nie posortował poprawnie danych (run #" << (i + 1) << ").\n";
                    delete[] data;
                    delete[] times;
                    exit(1);
                }
            }
            delete[] data;

        } else if (type == 2) {
            std::string* data = generator.generateData<std::string>();
            SortingAlgorithms<std::string> sorter(data, algorithm, size, pivot, gap, drunk);

            Timer timer;
            times[i] = sorter.sort(timer);

            if (algorithm == 4) {
                while (!sorter.isSorted()) {
                    ++retries;
                    sorter.decrDrunk();
                    std::cout << "[!] Retry #" << retries << " for attempt " << (i + 1) << " " << drunk << "\n";
                    Timer retryTimer;
                    times[i] += sorter.sort(retryTimer);
                }
            } else {
                if (!sorter.isSorted()) {
                    std::cerr << "[!] Błąd: Algorytm " << algorithm << " nie posortował poprawnie danych (run #" << (i + 1) << ").\n";
                    delete[] data;
                    delete[] times;
                    exit(1);
                }
            }
            delete[] data;

        } else if (type == 3) {
            BoardGame* data = generator.generateData<BoardGame>();
            SortingAlgorithms<BoardGame> sorter(data, algorithm, size, pivot, gap, drunk);

            Timer timer;
            times[i] = sorter.sort(timer);

            if (algorithm == 4) {
                while (!sorter.isSorted()) {
                    ++retries;
                    sorter.decrDrunk();
                    std::cout << "[!] Retry #" << retries << " for attempt " << (i + 1) << " " << drunk << "\n";
                    Timer retryTimer;
                    times[i] += sorter.sort(retryTimer);
                }
            } else {
                if (!sorter.isSorted()) {
                    std::cerr << "[!] Błąd: Algorytm " << algorithm << " nie posortował poprawnie danych (run #" << (i + 1) << ").\n";
                    delete[] data;
                    delete[] times;
                    exit(1);
                }
            }
            delete[] data;

        } else {
            delete[] times;
            std::cerr << "Błąd: Nieznany typ danych.\n";
            exit(1);
        }
    }

    DataHandler handler(outputFile);
    handler.writeBenchmarkResult(algorithm, type, size, runs, pivot, gap, drunk, distribution, times, retries);

    delete[] times;
}



int BenchmarkMode::parseInt(const char* s, const std::string& flagName) {
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

std::string BenchmarkMode::addFolderPrefix(const std::string& filename, const std::string& folder) {
    if (filename.find('/') == std::string::npos && filename.find('\\') == std::string::npos)
        return folder + "/" + filename;
    else
        return filename;
}
