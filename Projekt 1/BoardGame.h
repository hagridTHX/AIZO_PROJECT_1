#ifndef PROJEKTAIZO_BOARDGAME_H
#define PROJEKTAIZO_BOARDGAME_H

class BoardGame {
private:

    char name[26]{}; // ostatni znak to \0
    char publisher[26]{};
    int min_players;      // min 1
    int max_players;      // max 10
    int duration_minutes; // 5 - 480
    int complexity_level; // 1 - 10
    int joy_level;        // 1 - 10

    int countA() const;
    double calculateCoolness() const;

public:

    BoardGame();
    BoardGame(const char* nm, const char* pub, int minP, int maxP, int dur, int complexity, int joy);
    ~BoardGame();

    bool operator>(const BoardGame& bg) const;
    bool operator<(const BoardGame& bg) const;
    bool operator>=(const BoardGame& bg) const;
    bool operator<=(const BoardGame& bg) const;
    bool operator==(const BoardGame& bg) const;

    const char* getName() const;
    const char* getPublisher() const;
    int getMinPlayers() const;
    int getMaxPlayers() const;
    int getDuration() const;
    int getComplexity() const;
    int getJoy() const;
};

#endif //PROJEKTAIZO_BOARDGAME_H
