#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
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
        bool selected = false;
        Piece *piece = NULL;

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

/*
enum SquarePosition {
    a8, b8, c8, d8, e8, f8, g8, h8,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a1, b1, c1, d1, e1, f1, g1, h1,
};
*/

#endif
