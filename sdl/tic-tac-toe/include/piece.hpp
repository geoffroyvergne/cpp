#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <player.hpp>
#include <piece_type.hpp>

#ifndef CIRCLE
#define CIRCLE

class Piece {
    public:
        Piece(PieceType type);
        ~Piece();
        Player player;       
        SDL_Rect srcTextureParams; // Real texture size and placement
        SDL_Rect destTextureParams = { 250, 250,  50, 50 }; // Texture seen in game
        int caseNumber = 0;

        void togglePlayer(PieceType pieceype);
        void toggleColor();
        void display();
        void moveUp();
        void moveDown();
        void moveRight();
        void moveLeft();
        void cleanup();
};

#endif
