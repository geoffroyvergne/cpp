#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <snake.hpp>
//#include <block.hpp>
#include <block-type.hpp>
//#include <plateau.hpp>
#include <direction.hpp>

Snake::Snake() {
    currentDirection = none;
}

Snake::~Snake() { 
    cleanup();
}

/*void Snake::addBlock(Block *block) {
    
    blockList.push_back(block);

    SDL_Log("addblock %lu blocks", blockList.size());
}*/

void Snake::moveCurrentDirection() {

    this->blockList[0]->currentDirection = this->currentDirection;

    /*for (size_t i = this->blockList.size()-1; i >= this->blockList.size(); --i) {
        this->blockList[i]->currentDirection = this->blockList[i - 1]->currentDirection;
    }*/

    for (size_t i = 0; i < this->blockList.size(); ++i) {                
        this->blockList[i]->moveCurrentDirection();
    }

    for (size_t i = 0; i < this->blockList.size(); ++i) {        
        this->blockList[i]->currentDirection = this->currentDirection;        
    }
}

void Snake::changeDirection(Direction direction) { 
    if(isNewDirection(direction)) {
        this->currentDirection = direction;
        
        // this is a new direction add block
        Block *block = new Block(tail);

        if(blockList.size() >= 1) {
            block->currentDirection = this->blockList[blockList.size() -1]->currentDirection;
            block->destTextureParams = this->blockList[blockList.size() -1]->destTextureParams;
            //this->addBlock(block);

            blockList.push_back(block);
            SDL_Log("addblock %lu blocks", blockList.size());
        }
    }
}

bool Snake::isNewDirection(Direction direction) {
    if(direction != this->currentDirection) return true;
    else return false;
}

void Snake::display() {
    for (size_t i = 0; i < this->blockList.size(); ++i) {
        this->blockList[i]->display();
    }
}

void Snake::cleanup() {
    for (size_t i = 0; i < this->blockList.size(); ++i) {
        this->blockList[i]->cleanup();
    }
}

/*void Snake::moveUp() {
    for (size_t i = 0; i < this->blockList.size(); ++i) {
        if(this->blockList[i]->destTextureParams.y >= 100)
        this->blockList[i]->destTextureParams.y -= 50;
    }
}

void Snake::moveDown() {
    for (size_t i = 0; i < this->blockList.size(); ++i) {
        if(this->blockList[i]->destTextureParams.y <= 650)
        this->blockList[i]->destTextureParams.y += 50;
    }
}

void Snake::moveRight() {
    for (size_t i = 0; i < this->blockList.size(); ++i) {
        if(this->blockList[i]->destTextureParams.x <= 400)
        this->blockList[i]->destTextureParams.x += 50;
    }
}

void Snake::moveLeft() {
    for (size_t i = 0; i < this->blockList.size(); ++i) {
        if(this->blockList[i]->destTextureParams.x >= 100)
        this->blockList[i]->destTextureParams.x -= 50;
    }
}

void Snake::moveCurrentDirection() {
    switch(currentDirection) {
        case up:
            this->moveUp();
            break;

        case down:
            this->moveDown();
            break;

        case left:
            this->moveLeft();
            break;

        case right:
            this->moveRight();
            break;

        case none:
            break;
    }
}*/