#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <player.hpp>
#include <piece_type.hpp>

#ifndef CIRCLE
#define CIRCLE

class Piece {
    public:
        Piece(SDL_Renderer *render, PieceType type, SDL_Texture *sdl_texture);
        ~Piece();
        Player player;
        SDL_Renderer *render;
        std::string imagePath;
        SDL_Texture *sdl_texture;
        //SDL_Rect textureParams = { 30, 30,  90, 90 };
        //SDL_Rect textureParams;
        SDL_Rect srcTextureParams; // Real texture size and placement
        SDL_Rect destTextureParams = { 250, 250,  50, 50 }; // Texture seen in game
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
