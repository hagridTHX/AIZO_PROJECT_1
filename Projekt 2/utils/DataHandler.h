#ifndef PROJEKTAIZO_DATAHANDLER_H
#define PROJEKTAIZO_DATAHANDLER_H

#include <string>
#include "Edge.h"

class DataHandler {
private:
    std::string inputFile;
    std::string outputFile;

public:
    explicit DataHandler(const std::string& outputFileName);
    DataHandler(const std::string& inputFileName, const std::string& outputFileName);
    ~DataHandler();

    Edge* readGraphFromFile(int& edgeCount, int& vertexCount);
    void writeGraphBenchmarkResult(int problem, int algorithm, int representation,
                                   int vertices, int density, int runs, int* times);
};

#endif // PROJEKTAIZO_DATAHANDLER_H
