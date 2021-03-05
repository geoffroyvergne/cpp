#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <square-position.hpp>
#include <piece-type.hpp>
#include <color.hpp>

#ifndef CASE
#define CASE

class Square {
    public:
        Square(SDL_Renderer *render, SDL_Texture *sdl_texture, Color color, int width, int id);
        ~Square();
        int width;
        int id;
        Color color;
        SquarePosition position;
        PieceType pieceType;

        SDL_Renderer *render;
        SDL_Texture *sdl_texture;
        SDL_Rect srcTextureParams; // Real texture size and placement
        SDL_Rect destTextureParams; //= { 250, 250,  50, 50 }; // Texture seen in game

        Square* up();
        Square* down();
        Square* left();
        Square* right();
        
        void display();
        void cleanup();
};

#endif
