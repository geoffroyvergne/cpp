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
        void reset();

        void cursorUp();
        void cursorDown();
        void cursorLeft();
        void cursorRight();

        void deletePiece();
        void selectPiece();
        void validatePiece();
        void cancelSelectPiece();

        void renderView();
        void startLoop();
        void cleanup();
};

#endif
