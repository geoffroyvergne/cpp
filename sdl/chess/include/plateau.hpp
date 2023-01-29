#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include <array>
#include <vector>

#include <piece.hpp>
#include <square.hpp>

#ifndef PLATEAU
#define PLATEAU

class Plateau {
    public:
        Plateau(int squareWidth, int border);
        ~Plateau();

        int squareWidth;
        int border;
        
        std::vector<Square*> squareList;
        std::vector<Piece*> pieceList;       

        void init();

        void deletePieceById(int id);
        Piece* getPieceById(int id);
        Square* getSquareById(int id);
        bool caseAlreadyUsed(int id);
        void reset();
        std::string getSquarePositionById(int id);

        void display();
        void cleanup();
};

#endif
