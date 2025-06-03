#include "DataHandler.h"
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>

DataHandler::DataHandler(const std::string& outputFileName)
        : inputFile(""), outputFile(outputFileName) {}

DataHandler::DataHandler(const std::string& inputFileName, const std::string& outputFileName)
        : inputFile(inputFileName), outputFile(outputFileName) {}

DataHandler::~DataHandler() = default;

Edge* DataHandler::readGraphFromFile(int& edgeCount, int& vertexCount) {
    std::ifstream in(inputFile);
    if (!in.is_open()) {
        throw std::runtime_error("Cannot open input file: " + inputFile);
    }

    std::string headerLine;
    std::getline(in, headerLine);
    std::stringstream ss(headerLine);
    std::string edgeStr, vertexStr;

    std::getline(ss, edgeStr, '\t');
    std::getline(ss, vertexStr, '\t');

    edgeCount = std::stoi(edgeStr);
    vertexCount = std::stoi(vertexStr);

    Edge* edges = new Edge[edgeCount];

    for (int i = 0; i < edgeCount; ++i) {
        std::string line;
        if (!std::getline(in, line)) {
            delete[] edges;
            throw std::runtime_error("Unexpected end of file while reading edge " + std::to_string(i));
        }

        std::stringstream edgeStream(line);
        std::string fromStr, toStr, weightStr;

        std::getline(edgeStream, fromStr, '\t');
        std::getline(edgeStream, toStr, '\t');
        std::getline(edgeStream, weightStr, '\t');

        edges[i].u = std::stoi(fromStr);
        edges[i].v = std::stoi(toStr);
        edges[i].weight = std::stoi(weightStr);
    }

    in.close();
    return edges;
}

void DataHandler::writeGraphBenchmarkResult(int problem, int algorithm, int representation,
                                            int vertices, int density, int runs, int* times) {
    std::ofstream out(outputFile, std::ios::app);
    if (!out.is_open()) {
        throw std::runtime_error("Cannot open output file: " + outputFile);
    }

    out << "Problem;Algorithm;Representation;Vertices;Density;Runs;Mean;Min;Max;Median;StdDev\n";

    long long sum = 0;
    int minTime = times[0];
    int maxTime = times[0];
    for (int i = 0; i < runs; ++i) {
        sum += times[i];
        if (times[i] < minTime) minTime = times[i];
        if (times[i] > maxTime) maxTime = times[i];
    }

    double mean = static_cast<double>(sum) / runs;

    std::sort(times, times + runs);
    double median = (runs % 2 == 0)
                    ? (times[runs / 2 - 1] + times[runs / 2]) / 2.0
                    : times[runs / 2];

    double variance = 0.0;
    for (int i = 0; i < runs; ++i) {
        double diff = times[i] - mean;
        variance += diff * diff;
    }
    variance /= runs;
    double stddev = std::sqrt(variance);

    out << problem << ';' << algorithm << ';' << representation << ';'
        << vertices << ';' << density << ';' << runs << ';'
        << mean << ';' << minTime << ';' << maxTime << ';'
        << median << ';' << stddev << '\n';

    out.close();
}
