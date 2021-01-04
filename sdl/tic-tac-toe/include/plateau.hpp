#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <piece.hpp>
#include <player.hpp>

#ifndef PLATEAU
#define PLATEAU

class Plateau {
    public:
        Plateau(SDL_Renderer *render);
        SDL_Renderer *render;
        std::string imagePath = "../assets/plateau.png";
        SDL_Texture *sdl_texture;
        SDL_Rect textureParams = { 0, 0,  512, 512 };
        int casesUsed = 0;
        std::vector<Piece*> pieceList;

        void display();
        void addCases();
        int caseAlreadyUsed(Piece *piece);
        void displayPieces();
        Piece* addCurrentPiece(Piece *lastCurrentPiece, Player player);
        Player addNewPiece(Piece *currentPiece, Player player);
        int vectorContains(int caseNumber, Player player);
        Player lineDone();
};

#endif
