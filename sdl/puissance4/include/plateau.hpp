#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <piece.hpp>

#ifndef PLATEAU
#define PLATEAU

class Plateau {
    public:
        Plateau(SDL_Renderer *render, SDL_Texture *sdl_texture);
        ~Plateau();
        SDL_Renderer *render;
        //std::string imagePath = "../assets/puisance4-plateau.png";
        SDL_Texture *sdl_texture;
        //SDL_Rect textureParams = { 0, 50,  512, 460 };
        SDL_Rect srcTextureParams; // Real texture size and placement
        SDL_Rect destTextureParams; // Texture seen in game
        int casesUsed = 0;
        std::vector<Piece*> pieceList;

        void displayPieces();
        int addNewPiece(Piece *currentPiece);
        int caseAlreadyUsed(Piece *piece);
        void getCaseNumberByTextureParams(Piece *piece);
        Player lineDone();
        void display();
        void cleanup();
};

#endif
