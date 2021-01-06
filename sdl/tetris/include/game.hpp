#include <iostream>
#include <SDL.h>
#include <plateau.hpp>

#ifndef GAME
#define GAME

class Game {
    public:
        //Game();
        ~Game();
        std::string name = "tetris";
        int width = 500;
        int height = 500;
        int loopDelay = 10;

        SDL_Window *window;
        SDL_Renderer *render;
        Plateau *plateau;

        void init();
        void renderView();
        void startLoop();
        void cleanup();
};

#endif
