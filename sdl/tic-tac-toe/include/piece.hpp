#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <player.hpp>
#include <piece_type.hpp>

#ifndef CIRCLE
#define CIRCLE

struct Position {
    int caseNumber =0;
    int x = 0;
    int y = 0;
};

class Piece {
    public:
        Piece(PieceType type);
        ~Piece();
        Player player;       
        SDL_Rect srcTextureParams;
        SDL_Rect destTextureParams = { 250, 250,  50, 50 };
        Position position;

        void togglePlayer(PieceType pieceype);
        void display();
        void moveUp();
        void moveDown();
        void moveRight();
        void moveLeft();
        void cleanup();

        void caseNumberByTextureParams();
};

#endif
