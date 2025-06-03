#include "Timer.h"

Timer::Timer() : running(false) {}

void Timer::reset() {
    running = false;
    start_time = std::chrono::steady_clock::now();
    end_time = start_time;
}

int Timer::start() {
    if (!running) {
        start_time = std::chrono::steady_clock::now();
        running = true;
        return 0; // sukces
    }
    return -1; // timer już działa
}

int Timer::stop() {
    if (running) {
        end_time = std::chrono::steady_clock::now();
        running = false;
        return 0; // sukces
    }
    return -1; // timer nie był uruchomiony
}

int Timer::result() {
    if (running) {
        auto current_time = std::chrono::steady_clock::now();
        return static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time).count());
    } else {
        return static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count());
    }
}
