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

        Message *message;
        Plateau *plateau;

        void init();
        void renderView();
        void startLoop();
        void cleanup();
};

#endif
