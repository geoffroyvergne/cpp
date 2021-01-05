#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <piece.hpp>

Piece::Piece(SDL_Renderer *render, PieceType pieceType) {
    this->render = render;
    this->type = pieceType;
    //{ 26, 2,  55, 55 } initial position case

    //{ 26, 69,  55, 55 } first case
    textureParams = { 26, -3,  55, 55 };

    this->togglePlayer(pieceType);
}

Piece::~Piece() { 
    cleanup();
}

void Piece::togglePlayer(PieceType pieceType) {
    switch(pieceType) {
        case yellow_circle : 
            imagePath = "../assets/puisance4-yellow-spot.png"; 
            player = yellow;
            break;

        case red_circle : 
            imagePath = "../assets/puisance4-red-spot.png"; 
            player = red;
            break;
    }
    this->type = pieceType;

    if(sdl_texture != NULL) SDL_DestroyTexture(sdl_texture);
    sdl_texture = IMG_LoadTexture(render, imagePath.c_str());
}

void Piece::toggleColor() {
    //TODO Implement
}

void Piece::display() {
    SDL_RenderCopy(render, sdl_texture, NULL, &textureParams);
}

void Piece::moveRight() {
    if(textureParams.x <428) textureParams.x += 67;
}


void Piece::moveLeft() {
    if(textureParams.x >26) textureParams.x -= 67;
}

int Piece::moveUp() {
    if(textureParams.y >69) {
        textureParams.y -= 72;
        return false;
    }

    return true;
}

void Piece::moveDown() {
    if(textureParams.y <429) textureParams.y += 72;
}

void Piece::cleanup() {
    SDL_DestroyTexture(sdl_texture);
}