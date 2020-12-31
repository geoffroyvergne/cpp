#include <iostream>
#include <SDL.h>

#ifndef GAME
#define GAME

class Game {
    public:
        std::string name = "tic-tac-toe";
        int width = 512;
        int height = 512;
        int loopDelay = 100;
        SDL_Window *window;
        SDL_Renderer *render;
        void init();
        //void loadPlateau();
        void startLoop();
        void cleanup();
};

#endif
