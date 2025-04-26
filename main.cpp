#include <iostream>
#include <fstream>
#include <string>
#include "utils/Modes.h"

// Funkcja wyświetlająca pomoc (odczyt z pliku utils/helpScript.txt)
void printHelp() {
    std::ifstream helpFile(R"(C:\Users\Lookasz\CLionProjects\AIZO_PROJECT_1\utils\helpScript.txt)");
    if (!helpFile.is_open()) {
        std::cerr << "Nie można otworzyć pliku utils/helpScript.txt" << std::endl;
        return;
    }
    std::string line;
    while (std::getline(helpFile, line)) {
        std::cout << line << std::endl;
    }
    helpFile.close();
}

int main(int argc, char* argv[]) {
    if (argc == 1 || (argc > 1 && std::string(argv[1]) == "--help")) {
        printHelp();
        return 0;
    }

    std::string mode = argv[1];
    if (mode == "--file") {
        FileTestMode fileTestMode(argc, argv);
        fileTestMode.run();
    } else if (mode == "--test") {
        BenchmarkMode benchmarkMode(argc, argv);
        benchmarkMode.run();
    } else {
        std::cerr << "Błąd: Nieznany tryb. Użyj --help aby uzyskać pomoc." << std::endl;
        return 1;
    }
    return 0;
}
