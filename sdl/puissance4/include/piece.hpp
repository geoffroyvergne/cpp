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
        Piece(SDL_Renderer *render, PieceType type);
        ~Piece();
        PieceType type;
        Player player;
        SDL_Renderer *render;
        std::string imagePath;
        SDL_Texture *sdl_texture;
        SDL_Rect textureParams;
        int caseNumber = 0;
        Position position;

        void togglePlayer(PieceType pieceype);
        void toggleColor();
        int moveUp();
        void moveDown();
        void moveRight();
        void moveLeft();
        void display();
        void cleanup();
};

#endif
