#include <iostream>
#include <SDL.h>

#include <piece_type.hpp>
#include <player.hpp>

#ifndef PIECE
#define PIECE

struct Position {
    int caseNumber;
    int x;
    int y;
};

class Piece {    
    public:
        Piece(PieceType pieceType);
        ~Piece();
        PieceType pieceType = PieceType::none;
        Player player = Player::none;

        SDL_Rect srcTextureParams;
        SDL_Rect destTextureParams;

        Position position;
        bool rowFull = false;

        void togglePlayer(PieceType pieceype);
        bool moveUp();
        void moveDown();
        void moveRight();
        void moveLeft();
        void display();
        void cleanup();
};

#endif
