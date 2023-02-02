#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <snake.hpp>
//#include <block.hpp>
#include <block-type.hpp>
//#include <plateau.hpp>
#include <direction.hpp>
#include <list>

Snake::Snake() {
    currentDirection = none;
}

Snake::~Snake() { 
    cleanup();
}

void Snake::moveCurrentDirection() {
    if(this->currentDirection == none) return;
    
    //if(this->newDirection) {
        blockList.front()->switchType(tail);

        // add tail block to front
        Block *block = new Block(head);
        block->destTextureParams = blockList.front()->destTextureParams;
        blockList.push_front(block);

        // move head to new position
        blockList.front()->destTextureParams = getNextPositionByDirection(blockList.front()->destTextureParams, this->currentDirection);
    //}

    // if snake is too big remove last block
    if(blockList.size() >= 7){        
        blockList.pop_back();
    }
}

void Snake::changeDirection(Direction direction) {    
        //this->previousDirection = this->currentDirection;
        //this->newDirection = true;
        this->currentDirection = direction;
}

/*bool Snake::isNewDirection() {
    if(this->previousDirection != this->currentDirection) return true;
    else return false;
}*/

SDL_Rect Snake::getNextPositionByDirection(SDL_Rect destTextureParams, Direction direction) {
    switch(direction) {
        case up:
            destTextureParams.y = destTextureParams.y -50;
            break;

        case down:
            destTextureParams.y = destTextureParams.y +50;
            break;

        case left:
            destTextureParams.x = destTextureParams.x -50;
            break;

        case right:
            destTextureParams.x = destTextureParams.x +50;
            break;

        case none:
             
            break;
    }

        return destTextureParams;
}

void Snake::display() {
    /*for (size_t i = 0; i < this->blockList.size(); ++i) {
        this->blockList[i]->display();
    }*/

    for(Block* block : this->blockList) {
        block->display();
    }
}

void Snake::cleanup() {
    /*for (size_t i = 0; i < this->blockList.size(); ++i) {
        this->blockList[i]->cleanup();
    }*/

    for(Block* block : this->blockList) {
        block->cleanup();
    }
}