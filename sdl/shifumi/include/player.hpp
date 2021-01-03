#include <iostream>

#ifndef PLAYER
#define PLAYER

class Player {
    public:
        Player(std::string name);
        ~Player();
        std::string name;
        int score;
        int winner;
};

#endif
