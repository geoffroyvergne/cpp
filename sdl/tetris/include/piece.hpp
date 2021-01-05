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

        void addBlock(Block *block);

        void moveUp();
        void moveDown();
        void moveRight();
        void moveLeft();

        void rotate();

        void display();
        void cleanup();
};

#endif
