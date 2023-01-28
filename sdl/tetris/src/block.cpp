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
        case base : 
            srcTextureParams.x = 0;
            srcTextureParams.y = 0;
            break;

        case I : 
            srcTextureParams.x = 50;
            srcTextureParams.y = 0;
            break;

        case Z : 
            srcTextureParams.x = 0;
            srcTextureParams.y = 50;
            break;

        case L : 
            srcTextureParams.x = 50;
            srcTextureParams.y = 50;
            break;

        case J : 
            srcTextureParams.x = 0;
            srcTextureParams.y = 100;
            break;

        case T : 
            srcTextureParams.x = 50;
            srcTextureParams.y = 100;
            break;

        case S : 
            srcTextureParams.x = 0;
            srcTextureParams.y = 150;
            break;

        case O : 
            srcTextureParams.x = 50;
            srcTextureParams.y = 150;
            break;
    }
    
    destTextureParams = { 250, 50,  50, 50 };
}

Block::~Block() { 
    cleanup();
}

void Block::display() {
    SDL_RenderCopy(Core::getInstance()->getRender(), Core::getInstance()->getSdlTexture(), &srcTextureParams, &destTextureParams);
}

void Block::cleanup() {
    SDL_DestroyTexture(Core::getInstance()->getSdlTexture());
}
