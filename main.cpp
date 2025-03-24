#include <iostream>
#include "utils/Timer.h"

int main(int argc, char* argv[]) {
    Timer timer;
    timer.start();

    // symulacja operacji do zmierzenia
    for (volatile int i = 0; i < 1000000; ++i) {
        for (volatile int j = 0; j < 100; ++j);
    }

    timer.stop();

    std::cout << "Cza123132131s: " << timer.result() << " ms" << std::endl;
    timer.reset();
    std::cout << timer.result()<< std::endl;
    return 0;
}
