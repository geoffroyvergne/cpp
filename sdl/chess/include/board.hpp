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
        //void deletePiece(int x, int y);
        void deletePiece(Piece* piece);

        Color toggleColor(Color color);

        bool caseAlreadyUsed(Piece* piece);
        void reset();
        Piece* getNonePiece();
        bool validateMove(PieceType type, int origx, int origy, int x, int y);
        void showMove(PieceType type, int x, int y);

        void display();
        void displayBoard();
        void logBoard();
        void cleanup();
};

#endif
