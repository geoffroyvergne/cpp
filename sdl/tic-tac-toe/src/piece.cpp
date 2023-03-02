#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <piece.hpp>
#include <sdl-core.hpp>

Piece::Piece(PieceType pieceType) {
    srcTextureParams = { 30, 30, 90, 90 };
    destTextureParams = { 30, 30, 90, 90 };

    this->togglePlayer(pieceType);
    this->pieceType = pieceType;
}

Piece::~Piece() { 
    cleanup();
}

void Piece::togglePlayer(PieceType pieceType) {
    switch(pieceType) {
        case PieceType::black_circle : 
            srcTextureParams.x = 30;
            srcTextureParams.y = 22;
            player = Player::circle;
            break;

        case PieceType::black_cross : 
            srcTextureParams.x = 140;
            srcTextureParams.y = 20;
            player = Player::cross;
            break;

        case PieceType::red_circle : 
            srcTextureParams.x = 268;
            srcTextureParams.y = 19;
            player = Player::circle;
            break;

        case PieceType::red_cross : 
            srcTextureParams.x = 395;
            srcTextureParams.y = 20;
            player = Player::cross;
            break;

        case PieceType::none :
            player = Player::none;
            break;
    }
}

void Piece::display() {
    SDL_RenderCopy(SdlCore::getInstance()->getRender(), SdlCore::getInstance()->getSdlTexture(), &srcTextureParams, &destTextureParams);
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
    SDL_DestroyTexture(SdlCore::getInstance()->getSdlTexture());
}
