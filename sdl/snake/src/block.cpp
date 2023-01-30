#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <block.hpp>
#include <block-type.hpp>
#include <core.hpp>

Block::Block(BlockType type) {
    this->type = type;    
    srcTextureParams = { 0, 0,  50, 50 };

    switch(type) {
        case wall : 
            srcTextureParams.x = 0;
            srcTextureParams.y = 0;
            break;

        case head : 
            srcTextureParams.x = 50;
            srcTextureParams.y = 0;
            break;

         case tail : 
            srcTextureParams.x = 0;
            srcTextureParams.y = 0;
            break;
    }
    
    destTextureParams = { 250, 50,  50, 50 };
}

Block::~Block() { 
    cleanup();
}

void Block::moveUp() {
    if(this->destTextureParams.y >= 100)
    this->destTextureParams.y -= 50;
}

void Block::moveDown() {
    if(this->destTextureParams.y <= 650)
    this->destTextureParams.y += 50;
}

void Block::moveRight() {
    if(this->destTextureParams.x <= 400)
    this->destTextureParams.x += 50;
}

void Block::moveLeft() {
    if(this->destTextureParams.x >= 100)
    this->destTextureParams.x -= 50;
}

void Block::moveCurrentDirection() {
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
}

void Block::display() {
    SDL_RenderCopy(Core::getInstance()->getRender(), Core::getInstance()->getSdlTexture(), &srcTextureParams, &destTextureParams);
}

void Block::cleanup() {
    SDL_DestroyTexture(Core::getInstance()->getSdlTexture());
}