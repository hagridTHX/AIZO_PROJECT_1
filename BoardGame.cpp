#include "BoardGame.h"
#include <cstring>

// pomocnicza metoda do zliczania litery 'a' w nazwie wydawcy na potrzeby testów
int BoardGame::countA() const {
    int counter = 0;
    for (int i = 0; publisher[i] != '\0'; ++i)
        if (publisher[i] == 'a' || publisher[i] == 'A')
            ++counter;
    return counter;
}

// konstruktor z kopiowaniem ciągów znaków
BoardGame::BoardGame(const char* nm, const char* pub, int minP, int maxP, int dur, int complexity, int joy)
        : min_players(minP), max_players(maxP), duration_minutes(dur),
          complexity_level(complexity), joy_level(joy) {

    int i = 0;
    for (; i < 25 && nm[i] != '\0'; ++i)
        name[i] = nm[i];
    name[i] = '\0';

    i = 0;
    for (; i < 25 && pub[i] != '\0'; ++i)
        publisher[i] = pub[i];
    publisher[i] = '\0';
}

// obliczanie fajności
double BoardGame::calculateCoolness() const {
    double avg_players = (min_players + max_players) / 2.0;
    double base_coolness = (double(joy_level) / complexity_level) * (countA() + 1);
    double time_penalty = duration_minutes / 60.0;
    double name_length_bonus = static_cast<double>(strlen(name)) / 10.0;


    return (base_coolness + name_length_bonus) / (time_penalty * avg_players);
}



bool BoardGame::operator>(const BoardGame &bg) const {
    return calculateCoolness() > bg.calculateCoolness();
}

bool BoardGame::operator<(const BoardGame &bg) const {
    return calculateCoolness() < bg.calculateCoolness();
}

bool BoardGame::operator>=(const BoardGame &bg) const {
    return calculateCoolness() <= bg.calculateCoolness();
}

bool BoardGame::operator<=(const BoardGame &bg) const {
    return calculateCoolness() <= bg.calculateCoolness();
}

bool BoardGame::operator==(const BoardGame &bg) const {
    return calculateCoolness() == bg.calculateCoolness();
}
