#include <iostream>
#include <piece.hpp>

#ifndef PLAYER
#define PLAYER

enum class PlayerType {
    none,
    p1,
    p2
};

class Player {
    public:
        Player(std::string name, PlayerType type);
        ~Player();
        PlayerType type;
        std::string name;
        int score;
        int winner;
        Piece *piece;
};

#endif
