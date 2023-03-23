#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include <array>
#include <vector>

#include <piece.hpp>
#include <square.hpp>

#ifndef PLATEAU
#define PLATEAU

class Board {
    public:
        Board();
        ~Board();

        int squareWidth;

        std::vector<std::vector<Square>> squareList;
        std::vector<std::vector<Piece>> pieceList; 

        void init();
        void addPieces();
        //void resetPieces();
        Color toggleColor(Color color);

        void deletePiece(Piece* piece);
        bool caseAlreadyUsed(Piece* piece);
        void reset();
        Piece* getNonePiece();

        void display();
        void displayBoard();
        void logBoard();
        void cleanup();
};

#endif
