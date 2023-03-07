#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <piece_type.hpp>

#ifndef PIECE
#define PIECE

class Piece {
    public:
        Piece(PieceType type);
        ~Piece();
        std::string name;
        std::string imagePath;
        PieceType pieceype = PieceType::none;
        SDL_Rect srcTextureParams; 
        SDL_Rect destTextureParams;
        
        void togglePieceType(PieceType pieceType);
        void nextPiece();
        void randomPiece();
        void display();
        void cleanup();
};

#endif