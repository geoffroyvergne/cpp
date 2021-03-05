#include <iostream>
#include <SDL.h>
#include <piece.hpp>
#include <color.hpp>

Piece::Piece(SDL_Renderer *render, SDL_Texture *sdl_texture, PieceType type, Color color, int width) {
    this->width = width;
    this->color = color;
    this->render = render;
    this->sdl_texture = sdl_texture;
    this->type = type;

    init();
}

void Piece::init() {
    //srcTextureParams = { 514, 17, 70, 70 };

    switch(type) {
        case none : 
            srcTextureParams = { 0, 0, 10, 10 };
            break;

        case king :
            srcTextureParams = { 395, 20, 130, 130 };
            break; 

        case queen :
            srcTextureParams = { 263, 20, 130, 130 };
            break; 

        case rook :
            srcTextureParams = { -5, 20, 130, 130 };
            break; 

        case bishop :
            srcTextureParams = { 128, 20, 130, 130 };
            break; 

        case knight :
            srcTextureParams = { 530, 20, 130, 130 };
            break; 

        case paw :
            srcTextureParams = { 670, 25, 120, 120 };
            break; 
    }

    if (color == white) {
        srcTextureParams.y += 160;
    }

    destTextureParams = { 50, 50,  width, width };
}
 
Piece::~Piece() { 
    cleanup();
}

void Piece::display() {
    SDL_RenderCopy(render, sdl_texture, &srcTextureParams, &destTextureParams);
}

void Piece::cleanup() {
    SDL_DestroyTexture(sdl_texture);
}
