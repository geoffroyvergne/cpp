#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <square.hpp>

#ifndef CURSOR
#define CURSOR

class Cursor {
    public:
        Cursor();
        ~Cursor();
        int id;
        //int width;
        //int border;
        int x=0;
        int y=0;

        int origx=0;
        int origy=0;

        SDL_Color sdlColor = {128,0,0,50};

        //SDL_Rect srcTextureParams; 
        //SDL_Rect destTextureParams; 

        Piece *currentPiece = NULL;

        int sourceSquareId = 0;

        void up();
        void down();
        void left();
        void right();

        //int getId();

        void display();
        void cleanup();
};

#endif
