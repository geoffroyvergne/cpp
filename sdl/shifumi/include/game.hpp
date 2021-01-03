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

        SDL_Window *window;
        SDL_Renderer *render;
        Message *message;
        Player *player1;
        Player *player2;

        void init();
        void startLoop();
        void cleanup();
};

#endif
