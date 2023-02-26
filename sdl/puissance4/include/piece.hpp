#include <iostream>
#include <SDL.h>

#include <piece_type.hpp>
#include <player.hpp>

#ifndef PIECE
#define PIECE

struct Position {
    int caseNumber;
    int rowNumber;
    int lineNumber;
};

class Piece {
    public:
        Piece(PieceType type);
        ~Piece();
        PieceType type;
        Player player;

        SDL_Rect srcTextureParams; // Real texture size and placement
        SDL_Rect destTextureParams; // Texture seen in game
        int caseNumber = 0;
        Position position;

        void togglePlayer(PieceType pieceype);
        void toggleColor();
        bool moveUp();
        void moveDown();
        void moveRight();
        void moveLeft();
        void display();
        void cleanup();
};

#endif
