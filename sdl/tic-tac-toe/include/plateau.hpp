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
        Plateau();        
        SDL_Rect srcTextureParams; // Real texture size and placement
        SDL_Rect destTextureParams; // Texture seen in game
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
        int getCaseNumberByTextureParams(int x, int y);
};

#endif
