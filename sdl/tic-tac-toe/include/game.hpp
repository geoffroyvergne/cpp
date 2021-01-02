#include <iostream>
#include <vector>
#include <SDL.h>

#include <piece.hpp>
#include <plateau.hpp>
#include <player.hpp>

#ifndef GAME
#define GAME

class Game {
    public:
        std::string name = "tic-tac-toe";
        int width = 512;
        int height = 512;
        int loopDelay = 100;
        int circleScore = 0;
        int crossScore = 0;
        
        SDL_Window *window;
        SDL_Renderer *render;
        Player currentPlayer = circle;
        Piece *currentPiece;
        Plateau *plateau;
        Player winner = none;
          
        void init();
        void startLoop();
        void newGame();
        void increaseScore(Player player);
        std::string getScore();
        std::string getPlayer(Player player);
        void togglePlayer();
        void destroyTextures();
        void cleanup();       
};

#endif
