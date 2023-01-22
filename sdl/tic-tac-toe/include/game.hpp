#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>

#include <piece.hpp>
#include <plateau.hpp>
#include <player.hpp>

#ifndef GAME
#define GAME

class Game {
    public:
        ~Game();
        
        int loopDelay = 20;
        int circleScore = 0;
        int crossScore = 0;
        
        Player currentPlayer = circle;
        Piece *currentPiece;
        Plateau *plateau;
        Player winner = none;
        Player lastWinner = none;
        //Message *message;
        
        void renderView();
        void startLoop();
        void newGame();
        void increaseScore(Player player);
        std::string getScore();
        std::string getPlayer(Player player);
        void togglePlayer();
        void destroyTextures();
};

#endif
