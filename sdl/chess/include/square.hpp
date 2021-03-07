#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <square-position.hpp>
#include <piece-type.hpp>
#include <color.hpp>
#include <piece.hpp>

#ifndef CASE
#define CASE

class Square {
    public:
        Square(SDL_Renderer *render, SDL_Texture *sdl_texture, Color color, int width, int id);
        ~Square();
        int width;
        int id;
        Color color;
        std::string colorStr;
        SquarePosition position;
        bool selected = false;
        Piece *piece = NULL;

        SDL_Renderer *render;
        SDL_Texture *sdl_texture;
        SDL_Rect srcTextureParams; // Real texture size and placement
        SDL_Rect destTextureParams; //= { 250, 250,  50, 50 }; // Texture seen in game

        SDL_Rect srcSelectedTextureParams; // Real texture size and placement
        //SDL_Rect destSelectedTextureParams; //= { 250, 250,  50, 50 }; // Texture seen in game

        Square* up();
        Square* down();
        Square* left();
        Square* right();

        Square* diagUpRight();
        Square* diagUpLeft();
        Square* diagDownRight();
        Square* diagDownLeft();
        
        void display();
        void cleanup();
};

#endif
