#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <list>
#include <array>
#include <piece.hpp>
#include <player.hpp>

#ifndef PLATEAU
#define PLATEAU

class Plateau {
    public:
        Plateau();
        ~Plateau();        
        SDL_Rect srcTextureParams;
        SDL_Rect destTextureParams;
        int casesUsed = 0;
       
        std::array<std::array<Piece*, 7>, 6> piece2dList;
        
        int columnCount = 0;
        int rowCount = 0;
        int regularDiagonalCount = 0;
        int reverseDiagonalCount = 0;

        void clearPieceList();
        void displayPieces();
        Piece* addNewPiece(Piece *currentPiece);
        void displayTable();
        int caseAlreadyUsed(Piece *piece);
        void caseNumber(Piece *piece);
        Player lineDone(Piece *piece);
        void display();
        void cleanup();
        int countRed();
        int countpiece();
        void resetContainers();
};

#endif
