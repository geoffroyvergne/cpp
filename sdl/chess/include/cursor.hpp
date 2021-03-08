#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <square.hpp>

#ifndef CURSOR
#define CURSOR

class Cursor {
    public:
        Cursor(SDL_Renderer *render, SDL_Texture *sdl_texture, int width, int border);
        ~Cursor();
        int id;
        int width;
        int border;

        SDL_Renderer *render;
        SDL_Texture *sdl_texture;
        SDL_Rect srcTextureParams; // Real texture size and placement
        SDL_Rect destTextureParams; //= { 250, 250,  50, 50 }; // Texture seen in game

        //Square* sourceSquare = NULL;
        Piece *currentPiece = NULL;
        //Square* targetSquare = NULL;

        int sourceSquareId = 0;
        //int targetId = 0;

        void up();
        void down();
        void left();
        void right();

        int getId();

        void display();
        void cleanup();
};

#endif
