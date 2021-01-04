#include <iostream>
#include <SDL.h>

#include <message.hpp>
#include <player.hpp>

#ifndef GAME
#define GAME

class Game {
    public:
        //Game();
        ~Game();
        std::string name = "shifumi";
        int width = 512;
        int height = 512;
        int loopDelay = 10;
        int partyNumber = 0;

        SDL_Window *window;
        SDL_Renderer *render;

        Message *message;
        Player *player1;
        Player *player2;
        Player *playerNone;
        PlayerType winner;

        void init();
        void renderView();
        void startLoop();
        void result();
        void setWinner(PlayerType type);
        Player* getWinner(PlayerType type);
        std::string getScore();
        void newGame();
        void cleanup();
};

#endif
