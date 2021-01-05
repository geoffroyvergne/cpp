#include <iostream>
#include <SDL.h>

#include <plateau.hpp>
#include <message.hpp>

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

        SDL_Window *window;
        SDL_Renderer *render;

        Player currentPlayer = red;
        //Player winner = player_none;
        Piece *currentPiece;
        Message *message;
        Plateau *plateau;

        int redScore = 0;
        int yellowScore = 0;

        void init();
        void renderView();
        void startLoop();
        void togglePlayer();
        void validateRow();
        void newGame();
        void cleanup();
};

#endif
