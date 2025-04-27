#ifndef PROJEKTAIZO_DATAHANDLER_H
#define PROJEKTAIZO_DATAHANDLER_H

#include <string>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <type_traits>
#include <limits>
#include <algorithm>
#include <cmath>
#include "../BoardGame.h"
#include "Modes.h"

class DataHandler {
private:
    std::string inputFile;
    std::string outputFile;
    int size;

public:
    explicit DataHandler(const std::string& outputFileName)
            : inputFile(""), outputFile(addFolderPrefix(outputFileName, "output")), size(0) {}

    DataHandler(const std::string& inputFileName, const std::string& outputFileName)
            : inputFile(addFolderPrefix(inputFileName, "input")),
              outputFile(addFolderPrefix(outputFileName, "output")),
              size(-1) {}

    ~DataHandler() = default;

    int getSize() const {
        return size;
    }

    template<typename T>
    T* readFromFile();

    template<typename T>
    void writeToFile(T* data, int size);

    void writeBenchmarkResult(int algorithm, int type, int size, int runs,
                              int pivot, int gap, int drunk, int distribution,
                              int* times, int unsortedCount);

private:
    static std::string addFolderPrefix(const std::string& filename, const std::string& folder) {
        if (filename.find('/') == std::string::npos && filename.find('\\') == std::string::npos)
            return folder + "/" + filename;
        else
            return filename;
    }
};

template<typename T>
T* DataHandler::readFromFile() {
    std::ifstream in(inputFile);
    if (!in.is_open()) {
        throw std::runtime_error("Cannot open input file: " + inputFile);
    }

    in >> size;
    T* data = new T[size];

    if constexpr (std::is_same_v<T, BoardGame>) {
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        for (int i = 0; i < size; ++i) {
            std::string name, publisher;
            int minP, maxP, dur, complexity, joy;
            in >> name >> publisher >> minP >> maxP >> dur >> complexity >> joy;
            data[i] = BoardGame(name.c_str(), publisher.c_str(), minP, maxP, dur, complexity, joy);
        }
    } else {
        for (int i = 0; i < size; ++i) {
            in >> data[i];
        }
    }

    in.close();
    return data;
}

template<typename T>
void DataHandler::writeToFile(T* data, int dataSize) {
    std::ofstream out(outputFile);
    if (!out.is_open()) {
        throw std::runtime_error("Cannot open output file: " + outputFile);
    }

    out << dataSize << '\n';

    if constexpr (std::is_same_v<T, BoardGame>) {
        for (int i = 0; i < dataSize; ++i) {
            out << data[i].getName() << " "
                << data[i].getPublisher() << " "
                << data[i].getMinPlayers() << " "
                << data[i].getMaxPlayers() << " "
                << data[i].getDuration() << " "
                << data[i].getComplexity() << " "
                << data[i].getJoy() << '\n';
        }
    } else {
        for (int i = 0; i < dataSize; ++i) {
            out << data[i] << '\n';
        }
    }

    out.close();
}

inline void DataHandler::writeBenchmarkResult(int algorithm, int type, int data_size, int runs,
                                              int pivot, int gap, int drunk, int distribution,
                                              int* times, int unsortedCount) {
    bool writeHeader = false;

    std::ifstream infile(outputFile);
    if (!infile.is_open() || infile.peek() == std::ifstream::traits_type::eof()) {
        writeHeader = true;
    }
    infile.close();

    std::ofstream out(outputFile, std::ios::app);
    if (!out.is_open()) {
        throw std::runtime_error("Cannot open output file: " + outputFile);
    }

    if (writeHeader) {
        out << "Algorithm;Type;Size;Runs;Distribution;Pivot;Gap;Drunk;Mean;Min;Max;Median;StdDev;Unsorted\n";
    }

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
    double median;
    if (runs % 2 == 0) {
        median = (static_cast<double>(times[runs / 2 - 1]) + static_cast<double>(times[runs / 2])) / 2.0;
    } else {
        median = static_cast<double>(times[runs / 2]);
    }

    double variance = 0.0;
    for (int i = 0; i < runs; ++i) {
        double diff = static_cast<double>(times[i]) - mean;
        variance += diff * diff;
    }
    variance /= runs;
    double stddev = std::sqrt(variance);

    out << algorithm << ';'
        << (type != -1 ? std::to_string(type) : "") << ';'
        << data_size << ';'
        << runs << ';'
        << (distribution != -1 ? std::to_string(distribution) : "") << ';'
        << (pivot != -1 ? std::to_string(pivot) : "") << ';'
        << (gap != -1 ? std::to_string(gap) : "") << ';'
        << (drunk != -1 ? std::to_string(drunk) : "") << ';'
        << mean << ';'
        << minTime << ';'
        << maxTime << ';'
        << median << ';'
        << stddev << ';'
        << unsortedCount << '\n';

    out.close();
}

#endif // PROJEKTAIZO_DATAHANDLER_H
