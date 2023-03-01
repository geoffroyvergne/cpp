#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <piece.hpp>
#include <core.hpp>
#include <player.hpp>

Piece::Piece(PieceType pieceType) {
    this->type = pieceType;
    this->player = Player::player_none;

    srcTextureParams = { 151, 17, 90, 90 };
    destTextureParams = { 151, 17, 55, 55 };

    this->togglePlayer(pieceType);
}

Piece::~Piece() { 
    //cleanup();

    SDL_Log("Piece destructed");
}

void Piece::togglePlayer(PieceType pieceType) {
    switch(pieceType) {
        case yellow_circle : 
            srcTextureParams.x = 365;
            srcTextureParams.y = 17;
            player = Player::yellow;
            break;

        case red_circle : 
            srcTextureParams.x = 150;
            srcTextureParams.y = 14;
            player = Player::red;
            break;
        
        case piece_none :
            player = Player::player_none;
            break;
    }
    this->type = pieceType;
}

int Piece::getPlayer(Player player) {
    switch(player) {
        case Player::player_none : 
            return 0;
        break;

        case Player::yellow : 
            return 1;
        break;

        case Player::red : 
            return 2;
        break;
    }
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
    if(position.y == 1) return true;
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

/*Player Piece::getPlayer() {    
    return this->player;
}*/