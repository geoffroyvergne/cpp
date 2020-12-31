#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <piece.hpp>

Piece::Piece(SDL_Renderer *render, PieceType type) {
    this->render = render;

    switch(type) {
        case circle : imagePath = "../assets/circle.png"; break;
        case cross : imagePath = "../assets/cross.png"; break;
    }
    //imagePath = "../assets/circle.png";
    sdl_texture = IMG_LoadTexture(render, imagePath.c_str());
}

void Piece::display() {
    //SDL_RenderClear(render);
    SDL_RenderCopy(render, sdl_texture, NULL, &textureParams);
    //SDL_RenderPresent(render);
}

void Piece::moveUp() {
    
}
