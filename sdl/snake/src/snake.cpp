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
    if (pause) return;
    if (this->currentDirection == none) return;
    if (this->reachLimit()) return;
    if (this->touchTail()) return;
    
    blockList.front()->switchType(tail);

    // add tail block to front
    Block *block = new Block(head);
    block->destTextureParams = blockList.front()->destTextureParams;
    blockList.push_front(block);

    // move head to new position
    blockList.front()->destTextureParams = getNextPositionByDirection(blockList.front()->destTextureParams, this->currentDirection);
    
    // if snake is too big remove last block
    if(blockList.size() >= this->size){        
        blockList.pop_back();
    }
}

void Snake::changeDirection(Direction direction) {    
        if(currentDirection != direction) {        
            this->size++;
            this->currentDirection = direction;
        }
}

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

bool Snake::reachLimit() {
    switch(this->currentDirection) {
        case up:
            if(blockList.front()->destTextureParams.y <= 50) 
                return true;
            break;

        case down:
            if(blockList.front()->destTextureParams.y >= 700) 
                return true;
            break;

        case left:
            if(blockList.front()->destTextureParams.x >= 450) 
                return true;
            break;

        case right:
             if(blockList.front()->destTextureParams.x <= 50) 
                return true;
            break;

        case none:
            return false;
            break;
    }

    /*if(blockList.front()->destTextureParams.y <= 50 && this->currentDirection == up) return true;
    if(blockList.front()->destTextureParams.y >= 700 && this->currentDirection == down) return true;
    if(blockList.front()->destTextureParams.x >= 450 && this->currentDirection == right) return true;
    if(blockList.front()->destTextureParams.x <= 50 && this->currentDirection == left) return true;*/

    return false;
}

bool Snake::touchTail() {
    //SDL_Log("currentDirection %u", this->currentDirection);
    
    for(Block* block : this->blockList) {
        if(block->type == head) continue;

        switch(this->currentDirection) {
        case up:
            if(blockList.front()->destTextureParams.y == block->destTextureParams.y+50 && blockList.front()->destTextureParams.x == block->destTextureParams.x) 
                return true;
            break;

        case down:
            if(blockList.front()->destTextureParams.y == block->destTextureParams.y-50 && blockList.front()->destTextureParams.x == block->destTextureParams.x) 
                return true;
            break;

        case left:
            if(blockList.front()->destTextureParams.x == block->destTextureParams.x+50 && blockList.front()->destTextureParams.y == block->destTextureParams.y) 
                return true;
            break;

        case right:
            if(blockList.front()->destTextureParams.x == block->destTextureParams.x-50 && blockList.front()->destTextureParams.y == block->destTextureParams.y) 
                return true;
            break;

        case none:
            return false;
            break;
    }

        /*if(blockList.front()->destTextureParams.y == block->destTextureParams.y+50 && this->currentDirection == up) return true;
        if(blockList.front()->destTextureParams.y == block->destTextureParams.y-50 && this->currentDirection == down) return true;
        if(blockList.front()->destTextureParams.x == block->destTextureParams.x-50 && this->currentDirection == right) return true;
        if(blockList.front()->destTextureParams.x == block->destTextureParams.x+50 && this->currentDirection == left) return true;*/
    }
    
    return false;
}

void Snake::display() {
    for(Block* block : this->blockList) {
        block->display();
    }
}

void Snake::cleanup() {
    for(Block* block : this->blockList) {
        block->cleanup();
    }
}
