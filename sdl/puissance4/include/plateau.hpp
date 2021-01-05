#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <piece.hpp>

#ifndef PLATEAU
#define PLATEAU

class Plateau {
    public:
        Plateau(SDL_Renderer *render);
        ~Plateau();
        SDL_Renderer *render;
        std::string imagePath = "../assets/puisance4-plateau.png";
        SDL_Texture *sdl_texture;
        SDL_Rect textureParams = { 0, 50,  512, 460 };
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
