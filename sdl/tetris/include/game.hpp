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
        int width = 550;
        int height = 800;
        int loopDelay = 10;
        int iterations = 0;
        int pause = 0;

        SDL_Window *window;
        SDL_Renderer *render;
        Plateau *plateau;

        void init();
        void renderView();
        void startLoop();
        void moveDown();        
        void cleanup();
};

#endif
