#include <iostream>
#include <SDL.h>
#include <plateau.hpp>

#ifndef GAME
#define GAME

class Game {
    public:
        //Game();
        ~Game();
        std::string name = "snake";

        int width = 550;
        int height = 800;

        SDL_Window *window;
        SDL_Renderer *render;
        Plateau *plateau;

        void init();
        void renderView();
        void startLoop();
        void cleanup();
};

#endif
