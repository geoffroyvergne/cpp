#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <color.hpp>
#include <piece-type.hpp>

#ifndef PIECE
#define PIECE

class Piece {
    public:
        Piece(PieceType type, Color color);
        ~Piece();
        int id;
        int x;
        int y;
        PieceType type;
        std::string name;
        Color color;
        std::string colorStr;
                
        SDL_Rect srcTextureParams;
        SDL_Rect destTextureParams;
        
        void setId(int id);
        void setDestTextureParam();

        void up();
        void down();
        void left();
        void right();

        void init();
        void display();
        void cleanup();
};

#endif
