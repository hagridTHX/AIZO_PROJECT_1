#ifndef MODES_H
#define MODES_H

#include <string>

class FileTestMode {
public:
    int problem;
    int algorithm;
    int representation;
    std::string inputFile;
    std::string outputFile;
    int start;
    int end;

    FileTestMode(int argc, char* argv[]);
    void run();

private:
    static int parseInt(const char* s, const std::string& flagName);
    static std::string addFolderPrefix(const std::string& filename, const std::string& folder);
};

class BenchmarkMode {
public:
    int problem;
    int algorithm;
    int representation;
    int size;
    int density;
    int runs;
    std::string inputFile;
    std::string outputFile;
    int start;
    int end;

    BenchmarkMode(int argc, char* argv[]);
    void run();

private:
    static int parseInt(const char* s, const std::string& flagName);
    static std::string addFolderPrefix(const std::string& filename, const std::string& folder);
};

#endif // MODES_H