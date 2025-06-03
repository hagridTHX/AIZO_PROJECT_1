#include "Modes.h"
#include "../algorithms/MST.h"
#include "../algorithms/MaxFlow.h"
#include "../algorithms/ShortestPath.h"
#include "DataHandler.h"
#include <iostream>
#include <string>
#include <fstream>


FileTestMode::FileTestMode(int argc, char* argv[]) {
    if (argc < 6) {
        std::cerr << "Błąd: Za mało argumentów dla trybu FILE TEST MODE.\n";
        exit(1);
    }

    problem = parseInt(argv[2], "<problem>");
    algorithm = parseInt(argv[3], "<algorithm>");
    representation = parseInt(argv[4], "<representation>");
    inputFile = addFolderPrefix(argv[5], "input");

    int currentArg = 6;
    while (currentArg < argc) {
        std::string flag = argv[currentArg];
        if (flag == "--start") {
            if (currentArg + 1 < argc) {
                start = parseInt(argv[currentArg + 1], "--start");
                currentArg += 2;
            } else {
                std::cerr << "Błąd: Brak wartości dla flagi --start.\n";
                exit(1);
            }
        } else if (flag == "--end") {
            if (currentArg + 1 < argc) {
                end = parseInt(argv[currentArg + 1], "--end");
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
        outputFile = addFolderPrefix(inputFile + "OUT.txt", "output");
    }
}

void FileTestMode::run() {
    std::cout << "Rozpoczynanie testu plikowego:\n";
    std::cout << "Problem: " << problem << ", Algorytm: " << algorithm << ", Reprezentacja: " << representation << "\n";
    std::cout << "Plik wejściowy: " << inputFile << ", Plik wyjściowy: " << outputFile << "\n";

    int edgeCount = 0, vertexCount = 0;
    DataHandler handler(inputFile, outputFile);
    Edge* edgeList = handler.readGraphFromFile(edgeCount, vertexCount);

    Timer timer;

    if (representation == 0) {
        // === MACIERZ INCYDENCJI ===
        int** matrix = new int*[vertexCount];
        for (int i = 0; i < vertexCount; ++i) {
            matrix[i] = new int[edgeCount]();
        }
        for (int i = 0; i < edgeCount; ++i) {
            matrix[edgeList[i].u][i] = 1;
            matrix[edgeList[i].v][i] = 1;
        }

        if (problem == 0) {
            MST mst(matrix, 0);
            (algorithm == 0) ? mst.prim(timer) : mst.kruskal(timer);
        } else if (problem == 1) {
            if (start == -1 || end == -1) {
                std::cerr << "Brak wierzchołków start/end dla najkrótszej ścieżki.\n";
                exit(1);
            }
            ShortestPath sp(matrix, 0);
            (algorithm == 0) ? sp.dijkstra(timer, start, end) : sp.bellmanFord(timer, start, end);
        } else if (problem == 2) {
            MaxFlow mf(matrix, 0);
            mf.fordFulkerson(timer, start, end);
        }

        for (int i = 0; i < vertexCount; ++i)
            delete[] matrix[i];
        delete[] matrix;
    } else {
        // === LISTA SĄSIEDZTWA ===
        auto* graph = new Graph(vertexCount);
        for (int i = 0; i < edgeCount; ++i)
            graph->addEdge(edgeList[i].u, edgeList[i].v, edgeList[i].weight);

        if (problem == 0) {
            MST mst(graph, 1);
            (algorithm == 0) ? mst.prim(timer) : mst.kruskal(timer);
        } else if (problem == 1) {
            if (start == -1 || end == -1) {
                std::cerr << "Brak wierzchołków start/end dla najkrótszej ścieżki.\n";
                exit(1);
            }
            ShortestPath sp(graph, 1);
            (algorithm == 0) ? sp.dijkstra(timer, start, end) : sp.bellmanFord(timer, start, end);
        } else if (problem == 2) {
            MaxFlow mf(graph, 1);
            mf.fordFulkerson(timer, start, end);
        }

        delete graph;
    }

    delete[] edgeList;

    int duration = timer.result();
    std::ofstream out(outputFile);
    if (!out.is_open()) {
        std::cerr << "Nie można otworzyć pliku wyjściowego!\n";
        exit(1);
    }
    out << "Czas wykonania (ms): " << duration << "\n";
    out.close();
}



int FileTestMode::parseInt(const char* s, const std::string& flagName) {
    try {
        return std::stoi(s);
    } catch (...) {
        std::cerr << "Błąd: Niepoprawna wartość dla " << flagName << ".\n";
        exit(1);
    }
}

std::string FileTestMode::addFolderPrefix(const std::string& filename, const std::string& folder) {
    return (filename.find('/') == std::string::npos && filename.find('\\') == std::string::npos)
           ? folder + "/" + filename
           : filename;
}
