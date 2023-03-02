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
        
        Player currentPlayer = Player::circle;
        Piece *currentPiece;
        Plateau *plateau;
        Player winner = Player::none;
        Player lastWinner = Player::none;
        //Message *message;
        
        void renderView();
        void startLoop();
        void newGame();
        void increaseScore(Player player);
        std::string getScore();
        std::string getPlayer(Player player);
        void togglePlayer();
        void validate();
        void destroyTextures();
};

#endif
