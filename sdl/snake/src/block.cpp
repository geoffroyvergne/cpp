#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <block.hpp>
#include <block-type.hpp>

Block::Block(SDL_Renderer *render, BlockType type, SDL_Texture *sdl_texture) {
    this->render = render;
    this->type = type;
    this->sdl_texture = sdl_texture;
    
    srcTextureParams = { 0, 0,  50, 50 };

    switch(type) {
        case base : 
            srcTextureParams.x = 0;
            srcTextureParams.y = 0;
            break;

        case tail : 
            srcTextureParams.x = 50;
            srcTextureParams.y = 0;
            break;
    }
    
    destTextureParams = { 250, 50,  50, 50 };

    //if(sdl_texture != NULL) SDL_DestroyTexture(sdl_texture);

    //imagePath = "../assets/image-set.png"; 
    //sdl_texture = IMG_LoadTexture(render, imagePath.c_str());
}

Block::~Block() { 
    cleanup();
}

void Block::display() {
    SDL_RenderCopy(render, sdl_texture, &srcTextureParams, &destTextureParams);
}

void Block::cleanup() {
    SDL_DestroyTexture(sdl_texture);
}