#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>

#include <piece.hpp>
#include <plateau.hpp>
#include <player.hpp>
#include <message.hpp>

#ifndef GAME
#define GAME

class Game {
    public:
        std::string name = "tic-tac-toe";
        int width = 512;
        int height = 512;
        int loopDelay = 10;
        int circleScore = 0;
        int crossScore = 0;
        
        SDL_Window *window;
        SDL_Renderer *render;       
        
        Player currentPlayer = circle;
        Piece *currentPiece;
        Plateau *plateau;
        Player winner = none;
        Player lastWinner = none;
        Message *message;
        
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
