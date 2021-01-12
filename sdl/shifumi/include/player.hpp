#include <iostream>
#include <piece.hpp>

#ifndef PLAYER
#define PLAYER

enum PlayerType {
    player1Type,
    player2Type,
    playerNoneType
};

class Player {
    public:
        Player(std::string name, PlayerType type);
        ~Player();
        //SDL_Texture *sdl_texture;
        PlayerType type;
        std::string name;
        int score;
        int winner;
        Piece *piece;
};

#endif
