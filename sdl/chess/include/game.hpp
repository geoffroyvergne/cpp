#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include <plateau.hpp>

#ifndef GAME
#define GAME

class Game {
    public:
        Game();
        ~Game();
        std::string name = "Chess";
        int height = 500;
        int width = 600;
        int loopDelay = 100;

        SDL_Window *window;
        SDL_Renderer *render;
        SDL_Texture *sdl_texture_symbols;

        Plateau* plateau;

        void init();
        void renderView();
        void startLoop();
        void cleanup();
};

#endif

