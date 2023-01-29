#include <iostream>
#include <SDL.h>
#include <tile.hpp>
#include <core.hpp>

Tile::Tile(TileType tileType) { 
    //this->render = render;
    //this->sdl_texture = sdl_texture;
    this->tileType = tileType;

    switch(tileType) {
        case none : 
        break;

        case ground : 
            srcTextureParams = { 1, 131,  15, 16 };
            collide = true;
            break;

        case brick : 
            srcTextureParams = { 35, 96,  15, 16 };
            collide = true;
        break;

        case question_mark : 
            srcTextureParams = { 1, 62,  16, 17 };
            collide = true;
        break;

        // pipe
        case pipe_ul:
            srcTextureParams = { 377, 46,  16, 16 };
            collide = true;
        break;
        case pipe_ur:
            srcTextureParams = { 394, 46,  16, 16 };
            collide = true;
        break;
        case pipe_ll:
            srcTextureParams = { 377, 63,  16, 16 };
            collide = true;
        break;
        case pipe_lr:
            srcTextureParams = { 394, 63,  16, 16 };
            collide = true;
        break;

        // hill
        case hill_l:
            srcTextureParams = { 411, 97,  16, 16 };
        break;
        case hill_r:
            srcTextureParams = { 411, 97,  16, 16 };
            flip = SDL_FLIP_HORIZONTAL;
        break;
        case hill_cs:
            srcTextureParams = { 428, 97,  16, 16 };
        break;
        case hill_c:
            srcTextureParams = { 411, 95,  16, 16 };
        break;
        case hill_t:
            srcTextureParams = { 445, 63,  16, 16 };
        break;

        // bush
        case bush_l:
            srcTextureParams = { 222, 95,  16, 17 };
        break;
        case bush_c:
            srcTextureParams = { 239, 95,  16, 17 };
        break;
        case bush_r:
            srcTextureParams = { 256, 95,  16, 17 };
        break;

        // cloud
        case cloud_ul: 
            srcTextureParams = { 220, 62,  16, 17 };
        break;
        case cloud_ur: 
            srcTextureParams = { 256, 62,  16, 17 };
        break;
        case cloud_uc: 
            srcTextureParams = { 240, 62,  15, 17 };
        break;
        case cloud_ll: 
            srcTextureParams = { 220, 80,  16, 17 };
        break;
        case cloud_lr: 
            srcTextureParams = { 256, 80,  16, 17 };
        break;
        case cloud_lc:
            srcTextureParams = { 239, 80,  16, 17 };
        break;
    }
}

Tile::~Tile() { 
    cleanUp();
}

void Tile::display() { 
    //SDL_RenderCopy(Core::getInstance()->getRender(), Core::getInstance()->getSdlTextureLevels(), &srcTextureParams, &destTextureParams);
    SDL_RenderCopyEx(Core::getInstance()->getRender(), Core::getInstance()->getSdlTextureLevels(), &srcTextureParams ,&destTextureParams, 0.0, NULL, flip);

    //SDL_FLIP_NONE
    //SDL_FLIP_HORIZONTAL
}

void Tile::cleanUp() { 
    SDL_DestroyTexture(Core::getInstance()->getSdlTextureLevels());
}
