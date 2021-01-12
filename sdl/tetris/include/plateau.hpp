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
        Plateau(SDL_Renderer *render, SDL_Texture *sdl_texture);
        ~Plateau();
        std::vector<Block*> wallList;
        //std::vector<Piece*> pieceList;
        Piece *currentPiece;
        BlockType currentBlockType;
        SDL_Renderer *render;
        SDL_Texture *sdl_texture;
        //int collision = 0;

        int detectCollision();
        //void displayPieces();
        void toggleBlockType();
        void randomBlockType();
        void addPiece();
        void addWall();
        void displayCurrentPiece();
        void addCurrentPiece();
        void rotateCurrentPiece();
        void rotateCurrentPieceToPreviousPosition();
        void resetWall();
        int detectLineDone();
        void removeLine(int lineDone);
        void moveDownLine(int lineDone);
        int gameOver();
        void display();
        void cleanup();        
};

#endif
