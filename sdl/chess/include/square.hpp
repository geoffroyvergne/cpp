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
        Square(Color color, int id);
        ~Square();
        //int width;
        int id;
        int x;
        int y;
        Color color;
        SDL_Color sdlColor;

        std::string colorStr;
        SquarePosition position;
        bool selected = false;
        Piece *piece = NULL;
        
        //SDL_Rect srcTextureParams; 
        //SDL_Rect destTextureParams;

        //SDL_Rect srcSelectedTextureParams; 

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
