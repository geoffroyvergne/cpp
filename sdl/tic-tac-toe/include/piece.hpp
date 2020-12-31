#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#ifndef CIRCLE
#define CIRCLE

enum PieceType {
    circle,
    cross
};

class Piece {
    public:
        Piece(SDL_Renderer *render, PieceType type);
        SDL_Renderer *render;
        std::string imagePath;
        SDL_Texture *sdl_texture;
        SDL_Rect textureParams = { 30, 30,  90, 90 };
        void display();
        void moveUp();
        void moveDown();
        void moveRight();
        void moveLeft();
};

#endif
