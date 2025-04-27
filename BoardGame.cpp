#include "BoardGame.h"
#include <cstring>

int BoardGame::countA() const {
    int counter = 0;
    for (int i = 0; publisher[i] != '\0'; ++i)
        if (publisher[i] == 'a' || publisher[i] == 'A')
            ++counter;
    return counter;
}

BoardGame::BoardGame()
        : name(""), publisher(""), min_players(0), max_players(0), duration_minutes(0), complexity_level(0), joy_level(0) {}

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

BoardGame::~BoardGame() {};

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

const char* BoardGame::getName() const {
    return name;
}

const char* BoardGame::getPublisher() const {
    return publisher;
}

int BoardGame::getMinPlayers() const {
    return min_players;
}

int BoardGame::getMaxPlayers() const {
    return max_players;
}

int BoardGame::getDuration() const {
    return duration_minutes;
}

int BoardGame::getComplexity() const {
    return complexity_level;
}

int BoardGame::getJoy() const {
    return joy_level;
}
