#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <color.hpp>
#include <piece-type.hpp>

#ifndef PIECE
#define PIECE

class Piece {
    public:
        Piece(PieceType type, Color color, int width, int border);
        ~Piece();
        int width;
        int border;
        int id;
        PieceType type;
        std::string name;
        Color color;
        std::string colorStr;
        //bool selected = false;
                
        SDL_Rect srcTextureParams; // Real texture size and placement
        SDL_Rect destTextureParams; //= { 250, 250,  50, 50 }; // Texture seen in game

        bool validateMove(int currentId, int newId);
        int calculateNewId();
        void setId(int id);
        void setDestTextureParam(int id);

        void up();
        void down();
        void left();
        void right();

        void init();
        void display();
        void cleanup();
};

#endif
