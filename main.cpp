#include <iostream>
#include <fstream>
#include <string>

void printHelp();
void startTest();
void startBenchmark();

int main(int argc, char* argv[]) {

    if ((argc > 1 && std::string(argv[1]) == "--help") || argc == 1) {
        printHelp();
        return 0;
    }

    if (argc > 1 && std::string(argv[1]) == "--file") {
        startTest();
        return 0;
    }

    if (argc > 1 && std::string(argv[1]) == "--test") {
        startBenchmark();
        return 0;
    }
}

void printHelp() {
    // otwieramy plik helpScript.txt w trybie odczytu
    std::ifstream helpFile("utils/helpScript.txt");
    if (!helpFile.is_open()) {
        std::cerr << "Nie można otworzyć pliku utils/helpScript.txt" << std::endl;
        return;
    }

    // wczytujemy linia po linii i wyświetlamy
    std::string line;
    while (std::getline(helpFile, line)) {
        std::cout << line << std::endl;
    }

    helpFile.close();
}

void startTest() {

}

void startBenchmark() {

}
