#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <plateau.hpp>
#include <snake.hpp>

Plateau::Plateau() {
    //this->currentBlockType = head; 
    this->addWall();
}

Plateau::~Plateau() {
    cleanup();
}

void Plateau::addSnake() {    
    snake = new Snake();

    Block *block = new Block(head);
    block->destTextureParams.x = 250;
    block->destTextureParams.y = 400;

    //snake->addBlock(block);
    snake->blockList.push_front(block);
}

void Plateau::addWall() {
    for(int i=0; i<16; i++) {
        Block *block = new Block(wall);
        block->destTextureParams.x = 0;
        block->destTextureParams.y = (i) * 50;

        wallList.push_back(block);
    }

    for(int i=0; i<16; i++) {
        Block *block = new Block(wall);
        block->destTextureParams.x = 500;
        block->destTextureParams.y = (i) * 50;

        wallList.push_back(block);
    }

    for(int i=0; i<9; i++) {
        Block *block = new Block(wall);
        block->destTextureParams.x = (i+1) * 50;
        block->destTextureParams.y = 750;

        wallList.push_back(block);
    }

    for(int i=0; i<9; i++) {
        Block *block = new Block(wall);
        block->destTextureParams.x = (i+1) * 50;
        block->destTextureParams.y = 0;

        wallList.push_back(block);
    }
}

void Plateau::display() {
    for (size_t i = 0; i < this->wallList.size(); ++i) {
        this->wallList[i]->display();
    }
}

void Plateau::cleanup() {
    for (size_t i = 0; i < this->wallList.size(); ++i) {
        this->wallList[i]->cleanup();
    }
}

