#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <piece.hpp>

#ifndef PLATEAU
#define PLATEAU

class Plateau {
    public:
        Plateau();
        ~Plateau();        
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
