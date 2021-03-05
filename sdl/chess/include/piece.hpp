#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <color.hpp>
#include <piece-type.hpp>

#ifndef PIECE
#define PIECE

class Piece {
    public:
        Piece(SDL_Renderer *render, SDL_Texture *sdl_texture, PieceType type, Color color, int width);
        ~Piece();
        int width;
        PieceType type;
        Color color;
        bool selected = false;
        

        SDL_Renderer *render;
        SDL_Texture *sdl_texture;
        SDL_Rect srcTextureParams; // Real texture size and placement
        SDL_Rect destTextureParams; //= { 250, 250,  50, 50 }; // Texture seen in game

        void init();
        void display();
        void cleanup();
};

#endif
