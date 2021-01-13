#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <piece.hpp>

Piece::Piece(SDL_Renderer *render, PieceType pieceType, SDL_Texture *sdl_texture) {
    this->render = render;
    this->type = pieceType;
    this->sdl_texture = sdl_texture;
    //{ 26, 2,  55, 55 } initial position case

    //{ 26, 69,  55, 55 } first case
    //textureParams = { 26, -3,  55, 55 };
    srcTextureParams = { 151, 17,  90, 90 };
    destTextureParams = { 151, 17,  55, 55 };

    this->togglePlayer(pieceType);
}

Piece::~Piece() { 
    cleanup();
}

void Piece::togglePlayer(PieceType pieceType) {
    switch(pieceType) {
        case yellow_circle : 
            //imagePath = "../assets/puisance4-yellow-spot.png"; 
            srcTextureParams.x = 365;
            srcTextureParams.y = 17;
            player = yellow;
            break;

        case red_circle : 
            //imagePath = "../assets/puisance4-red-spot.png"; 
            srcTextureParams.x = 150;
            srcTextureParams.y = 14;
            player = red;
            break;
    }
    this->type = pieceType;

    //if(sdl_texture != NULL) SDL_DestroyTexture(sdl_texture);
    //sdl_texture = IMG_LoadTexture(render, imagePath.c_str());
}

void Piece::toggleColor() {
    //TODO Implement
}

void Piece::display() {
    //SDL_RenderCopy(render, sdl_texture, NULL, &textureParams);
    SDL_RenderCopy(render, sdl_texture, &srcTextureParams, &destTextureParams);
}

void Piece::moveRight() {
    if(destTextureParams.x <360) destTextureParams.x += 67;
}


void Piece::moveLeft() {
    if(destTextureParams.x >26) destTextureParams.x -= 67;
}

int Piece::moveUp() {
    if(destTextureParams.y >69) {
        destTextureParams.y -= 68;
        return false;
    }

    return true;
}

void Piece::moveDown() {
    if(destTextureParams.y <429) destTextureParams.y += 72;
}

void Piece::cleanup() {
    //SDL_DestroyTexture(sdl_texture);
}