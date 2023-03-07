#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <piece.hpp>
#include <sdl-core.hpp>
#include <SDL2_gfxPrimitives.h>

Piece::Piece(PieceType pieceType) {
    //position.x=250;
    //position.y=250;

    this->togglePlayer(pieceType);
    this->pieceType = pieceType;
}

Piece::~Piece() { 
    cleanup();
}

void Piece::togglePlayer(PieceType pieceType) {
    switch(pieceType) {
        case PieceType::black_circle : 
            color={0, 0, 0, 255};
            
            player = Player::circle;
            break;

        case PieceType::black_cross : 
            color={0, 0, 0, 255};

            player = Player::cross;
            break;

        case PieceType::red_circle : 
            color={255, 0, 0, 255};

            player = Player::circle;
            break;

        case PieceType::red_cross : 
            color={255, 0, 0, 255};

            player = Player::cross;
            break;

        case PieceType::none :
            player = Player::none;
            break;
    }
}

void Piece::display() {
    switch(player) {
        case Player::circle:
            displayCircle(color);
        break;

        case Player::cross:
            displayCross(color);
        break;

        case Player::none:
        break;
    }
}

void Piece::displayCross(SDL_Color color) {
    //SDL_Log("display piece cross texture.x %d texture.y %d texture.x %d texture.y %d", texture.x-size, texture.y-size, texture.x+size, texture.y+size);
    thickLineRGBA(SdlCore::getInstance()->getRender(), texture.x-size, texture.y-size, texture.x+size, texture.y+size, thick, color.r, color.g, color.b, color.a);
    thickLineRGBA(SdlCore::getInstance()->getRender(),  texture.x-size, texture.y+size, texture.x+size, texture.y-size, thick, color.r, color.g, color.b, color.a);
}

void Piece::displayCircle(SDL_Color color) {
    //SDL_Log("display piece circle texture.x %d texture.y %d", texture.x, texture.y);
    filledCircleRGBA(SdlCore::getInstance()->getRender(), texture.x, texture.y, 50, color.r, color.g, color.b, color.a);
    filledCircleRGBA(SdlCore::getInstance()->getRender(), texture.x, texture.y, size -thick, 255, 255, 255, 255);
}

void Piece::moveUp() {
    if(this->position.y == 1) return;
    this->position.y --;
    this->texture.y -=150;
}

void Piece::moveDown() {
    if(this->position.y == 3) return;
    this->position.y ++;
    this->texture.y +=150;
}

void Piece::moveRight() {
    if(this->position.x == 3) return;
    this->position.x ++;
    this->texture.x +=150;
}

void Piece::moveLeft() {
    if(this->position.x == 1) return;
    this->position.x --;
    this->texture.x -=150;
}

void Piece::cleanup() {
    //SDL_DestroyTexture(SdlCore::getInstance()->getSdlTexture());
}
