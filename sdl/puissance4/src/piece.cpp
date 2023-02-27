#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <piece.hpp>
#include <core.hpp>

Piece::Piece(PieceType pieceType) {
    this->type = pieceType;
    
    srcTextureParams = { 151, 17, 90, 90 };
    destTextureParams = { 151, 17, 55, 55 };

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

void Piece::display() {
    SDL_RenderCopy(Core::getInstance()->getRender(), Core::getInstance()->getSdlTexture(), &srcTextureParams, &destTextureParams);
}

void Piece::moveRight() {
    if(position.x <7) {
        destTextureParams.x += 67;
        position.x++;
    }
}

void Piece::moveLeft() {
    if(position.x >1) {
        destTextureParams.x -= 67;
        position.x--;
    }
}

bool Piece::moveUp() {
    if(position.y == 0) return true;
    destTextureParams.y -= 67;
    position.y--;

    return false;
}

void Piece::moveDown() {
    if(position.y >1) {
        destTextureParams.y += 67;
        position.y++;
    }
}

void Piece::cleanup() {
    //SDL_DestroyTexture(Core::getInstance()->getSdlTexture());
}
