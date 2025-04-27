#ifndef MODES_H
#define MODES_H

#include <string>

class FileTestMode {
public:
    int algorithm;
    int type;
    int pivot;
    int gap;
    int drunk;
    std::string inputFile;
    std::string outputFile;

    FileTestMode(int argc, char* argv[]);
    void run() const;

private:
    static int parseInt(const char* s, const std::string& flagName);
    static std::string addFolderPrefix(const std::string& filename, const std::string& folder);
};

class BenchmarkMode {
public:
    int algorithm;
    int type;
    int size;
    int pivot;
    int gap;
    int drunk;
    int distribution;
    int runs;
    std::string outputFile;

    BenchmarkMode(int argc, char* argv[]);
    void run() const;

private:
    static int parseInt(const char* s, const std::string& flagName);
    static std::string addFolderPrefix(const std::string& filename, const std::string& folder);
};

#endif // MODES_H
