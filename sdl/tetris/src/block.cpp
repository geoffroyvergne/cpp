#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <block.hpp>
#include <block-type.hpp>

Block::Block(SDL_Renderer *render, BlockType type) {
    this->render = render;
    this->type = type;

    switch(type) {
        case base : 
            imagePath = "../assets/tetris-brick-base-grey.jpg"; 
            break;

        case I : 
            imagePath = "../assets/tetris-brick-blue-I.jpg"; 
            break;

        case Z : 
            imagePath = "../assets/tetris-brick-green-Z.jpg"; 
            break;

        case L : 
            imagePath = "../assets/tetris-brick-orange-L.jpg"; 
            break;

        case J : 
            imagePath = "../assets/tetris-brick-pink-J.jpg"; 
            break;

        case T : 
            imagePath = "../assets/tetris-brick-purple-T.jpg"; 
            break;

        case S : 
            imagePath = "../assets/tetris-brick-red-S.jpg"; 
            break;

        case O : 
            imagePath = "../assets/tetris-brick-yellow-O.jpg"; 
            break;
    }

    textureParams = { 200, 50,  50, 50 };

    //if(sdl_texture != NULL) SDL_DestroyTexture(sdl_texture);
    sdl_texture = IMG_LoadTexture(render, imagePath.c_str());
}

Block::~Block() { 
    cleanup();
}

void Block::display() {
    SDL_RenderCopy(render, sdl_texture, NULL, &textureParams);
}

void Block::cleanup() {
    SDL_DestroyTexture(sdl_texture);
}
