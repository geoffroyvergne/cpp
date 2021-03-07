#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include <plateau.hpp>
#include <cursor.hpp>

#ifndef GAME
#define GAME

class Game {
    public:
        Game();
        ~Game();
        std::string name = "Chess";        
        int width = 600;
        int loopDelay = 100;
        int border = 50;

        SDL_Window *window;
        SDL_Renderer *render;
        SDL_Texture *sdl_texture_symbols;

        Plateau* plateau;
        Cursor* cursor;

        void init();
        void renderView();
        void startLoop();
        void cleanup();
};

#endif
