#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <piece_type.hpp>

#ifndef PIECE
#define PIECE

class Piece {
    public:
        Piece(SDL_Renderer *render, PieceType type, SDL_Texture *sdl_texture);
        ~Piece();
        std::string name;
        std::string imagePath;
        PieceType pieceype = none;
        SDL_Texture *sdl_texture;
        //SDL_Rect textureParams;
        SDL_Rect srcTextureParams; // Real texture size and placement
        SDL_Rect destTextureParams; // Texture seen in game
        SDL_Renderer *render;
        
        void togglePieceType(PieceType pieceType);
        void nextPiece();
        void randomPiece();
        void display();
        void cleanup();
};

#endif