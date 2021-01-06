#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <block.hpp>
#include <piece.hpp>

#ifndef PLATEAU
#define PLATEAU

class Plateau {
    public:
        Plateau(SDL_Renderer *render);
        ~Plateau();
        std::vector<Block*> wallList;
        std::vector<Piece*> pieceList;
        Piece *currentPiece;
        BlockType currentBlockType;
        SDL_Renderer *render;        

        void displayPieces();
        void toggleBlockType();
        void addPiece();
        void addWall();
        void displayCurrentPiece();
        void addCurrentPiece();
        void rotateCurrentPiece();
        void display();
        void cleanup();
        
};

#endif
