#include <iostream>
#include <vector>
#include <list>
#include <array>
#include <SDL.h>
//#include <SDL_image.h>
#include <piece.hpp>
#include <player.hpp>

#ifndef PLATEAU
#define PLATEAU

class Plateau {
    public:
        Plateau();        
        SDL_Rect srcTextureParams;
        SDL_Rect destTextureParams;
        int casesUsed = 0;
        std::array<std::array<Piece*, 3>, 3> piece2dList;

        /*int rowContainer[3][3];
        int columnContainer[3][3];
        int regularDiagonalContainer[3][3];
        int oppositDiagonalContainer[3][3];*/

        int columnCount = 0;
        int rowCount = 0;
        int regularDiagonalCount = 0;
        int reverseDiagonalCount = 0;

        void clearPieceList();
        void display();
        void displayPieces();
        void drawLineDone();
        void drawPlateau();
        //void drawRect(SDL_Rect rect, SDL_Color color);
        
        Piece* addCurrentPiece(Piece *lastCurrentPiece, Player player);
        Player addNewPiece(Piece *currentPiece, Player player);
        void displayTable();

        int caseAlreadyUsed(Piece *piece);
        void caseNumber(Piece *piece);
        int countpiece();   
        
        Player checkWin(Piece *piece);
        void resetContainers();

        //int pieceListContains(int caseNumber, Player player);
        //Player lineDone(Player currentPlayer);
};

#endif
