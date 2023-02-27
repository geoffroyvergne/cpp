#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <piece.hpp>
#include <core.hpp>

Piece::Piece(PieceType pieceype) {
    srcTextureParams = { 30, 30, 90, 90 };
    destTextureParams = { 30, 30, 90, 90 };

    this->togglePlayer(pieceype);
}

Piece::~Piece() { 
    cleanup();
}

void Piece::togglePlayer(PieceType pieceype) {
    switch(pieceype) {
        case black_circle : 
            srcTextureParams.x = 30;
            srcTextureParams.y = 22;
            player = circle;
            break;

        case black_cross : 
            srcTextureParams.x = 140;
            srcTextureParams.y = 20;
            player = cross;
            break;

        case red_circle : 
            srcTextureParams.x = 268;
            srcTextureParams.y = 19;
            player = circle;
            break;

        case red_cross : 
            srcTextureParams.x = 395;
            srcTextureParams.y = 20;
            player = cross;
            break;

        case piece_none :
            break;
    }
}

void Piece::display() {
    SDL_RenderCopy(Core::getInstance()->getRender(), Core::getInstance()->getSdlTexture(), &srcTextureParams, &destTextureParams);
}

void Piece::moveUp() {
    if(position.y >1) {
        destTextureParams.y -= 180;
        position.y--;
    }
}

void Piece::moveDown() {
    if(position.y <3) {
        destTextureParams.y += 180;
        position.y++;
    }
}

void Piece::moveRight() {
    if(position.x <3) {
        destTextureParams.x += 180;
        position.x++;
    }
}

void Piece::moveLeft() {
    if(position.x >1) {
        destTextureParams.x -= 180;
        position.x--;
    }
}

void Piece::cleanup() {
    SDL_DestroyTexture(Core::getInstance()->getSdlTexture());
}
