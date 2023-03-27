#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <square.hpp>
#include <color.hpp>

#ifndef CURSOR
#define CURSOR

class Cursor {
    public:
        Cursor();
        ~Cursor();
        int id;
        int x=0;
        int y=0;

        int origx=0;
        int origy=0;

        SDL_Color sdlColor;
        Color color;

        Piece *currentPiece = NULL;

        int sourceSquareId = 0;

        void setColor();

        void up();
        void down();
        void left();
        void right();

        void display();
        void cleanup();
};

#endif
