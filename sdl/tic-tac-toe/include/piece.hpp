#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <player.hpp>
#include <piece_type.hpp>

#ifndef CIRCLE
#define CIRCLE

class Piece {
    public:
        Piece(SDL_Renderer *render, PieceType type);
        ~Piece();
        Player player;
        SDL_Renderer *render;
        std::string imagePath;
        SDL_Texture *sdl_texture = NULL;
        //SDL_Rect textureParams = { 30, 30,  90, 90 };
        SDL_Rect textureParams;
        int caseNumber = 0;

        void togglePlayer(PieceType pieceype);
        void toggleColor();
        void getCaseNumberByTextureParams();
        void display();
        void moveUp();
        void moveDown();
        void moveRight();
        void moveLeft();
        void cleanup();
};

#endif
