#include <iostream>
#include <SDL.h>

#include <plateau.hpp>

#include <core.hpp>

#ifndef GAME
#define GAME

class Game {
    public:
        //Game();
        ~Game();
        std::string name = "puissance4";
        int width = 512;
        int height = 512;
        int loopDelay = 10;
        int partyNumber = 0;        

        Player currentPlayer = Player::red;
        Player winner = Player::player_none;
        Piece *currentPiece;
        Plateau *plateau;

        int redScore = 0;
        int yellowScore = 0;

        void renderView();
        void startLoop();
        void togglePlayer();
        void validateRow();
        void addPiece();
        void newGame();
};

#endif
