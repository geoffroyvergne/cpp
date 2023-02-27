#include <iostream>
#include <vector>
#include <list>
#include <array>
#include <SDL.h>
#include <SDL_image.h>
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

        int rowContainer[2][3] = {{0,0,0}, {0,0,0}};
        int columnContainer[2][3] = {{0,0,0}, {0,0,0}};

        int regularDiagonalContainer[2][3] = {{0,0,0}, {0,0,0}};
        int oppositDiagonalContainer[2][3] = {{0,0,0}, {0,0,0}};

        void clearPieceList();
        void display();
        void displayPieces();
        
        Piece* addCurrentPiece(Piece *lastCurrentPiece, Player player);
        Player addNewPiece(Piece *currentPiece, Player player);
        void displayTable();

        int caseAlreadyUsed(Piece *piece);
        void caseNumber(Piece *piece);
        int countpiece();   
        
        Player checkWin(Player player, int row, int column, int boardSize);
        void resetContainers(int boardSize);

        //int pieceListContains(int caseNumber, Player player);
        //Player lineDone(Player currentPlayer);
};

#endif
