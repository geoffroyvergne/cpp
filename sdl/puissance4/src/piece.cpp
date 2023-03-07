#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <piece.hpp>
#include <sdl-core.hpp>
#include <player.hpp>
#include <SDL2_gfxPrimitives.h>

Piece::Piece(PieceType type) {
    this->type = type;
    this->player = Player::none;

    this->togglePlayer(type);
}

Piece::~Piece() { 
    //cleanup();
}

void Piece::togglePlayer(PieceType type) {
    switch(type) {
        case PieceType::yellow : 
            player = Player::yellow;
            color = {255,240,0,255};
            break;

        case PieceType::red : 
            player = Player::red;
            color = {255,0,0,255};
            break;
        
        case PieceType::none :
            player = Player::none;
            break;
    }
    this->type = type;
}

void Piece::display() {
    filledCircleRGBA(SdlCore::getInstance()->getRender(), texture.x, texture.y, 30, color.r, color.g, color.b, color.a);
}

void Piece::moveRight() {
    if(position.x >=7) return;
    texture.x += 67;
    position.x++;
}

void Piece::moveLeft() {
    if(position.x <=1) return;
    texture.x -= 67;
    position.x--;
}

bool Piece::moveUp() {
    if(position.y == 1) return true;
    texture.y  -= 73;
    position.y--;

    return false;
}

void Piece::moveDown() {
    if(position.y >5) return;
    texture.y += 73;
    position.y++;
}

void Piece::cleanup() {
    //SDL_DestroyTexture(Core::getInstance()->getSdlTexture());
}
