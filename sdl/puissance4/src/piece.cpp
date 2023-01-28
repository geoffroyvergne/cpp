#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <piece.hpp>
#include <core.hpp>

Piece::Piece(PieceType pieceType) {
    this->type = pieceType;
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
            srcTextureParams.x = 365;
            srcTextureParams.y = 17;
            player = yellow;
            break;

        case red_circle : 
            srcTextureParams.x = 150;
            srcTextureParams.y = 14;
            player = red;
            break;
    }
    this->type = pieceType;
}

void Piece::toggleColor() {
    //TODO Implement
}

void Piece::display() {
    SDL_RenderCopy(Core::getInstance()->getRender(), Core::getInstance()->getSdlTexture(), &srcTextureParams, &destTextureParams);
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
    //SDL_DestroyTexture(Core::getInstance()->getSdlTexture());
}