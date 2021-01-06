#include <iostream>
#include <vector>
#include <SDL.h>

#include <block.hpp>

#ifndef PIECE
#define PIECE

class Piece {
    public:
        Piece(SDL_Renderer *render, BlockType type);
        ~Piece();

        std::vector<Block*> blockList;
        SDL_Renderer *render;
        BlockType type;
        int position = 0;

        int positionX = 200;
        int positionY = 50;

        void addBlock(Block *block);
        void nextPosition();

        void addBase(BlockType type);

        void addI(BlockType type);
        void rotateI(BlockType type);

        void addZ(BlockType type);
        void rotateZ(BlockType type);

        void addL(BlockType type);
        void rotateL(BlockType type);

        void addJ(BlockType type);
        void rotateJ(BlockType type);

        void addT(BlockType type);
        void rotateT(BlockType type);

        void addS(BlockType type);
        void rotateS(BlockType type);

        void addO(BlockType type);
        void rotateO(BlockType type);

        void moveUp();
        void moveDown();
        void moveRight();
        void moveLeft();

        void rotate();

        void display();
        void cleanup();
};

#endif
