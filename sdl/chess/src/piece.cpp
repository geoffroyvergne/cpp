#include <iostream>
#include <SDL.h>
#include <piece.hpp>
#include <color.hpp>
#include <sdl-core.hpp>

Piece::Piece(PieceType type, Color color) {    
    this->color = color;
    this->type = type;

    init();
}

void Piece::init() {
    switch(type) {
        case none : 
            srcTextureParams = { 0, 0, 10, 10 };
            this->name = "none";
            break;

        case king :
            srcTextureParams = { 395, 20, 130, 130 };
            this->name = "king";
            break; 

        case queen :
            srcTextureParams = { 263, 20, 130, 130 };
            this->name = "queen";
            break; 

        case rook :
            srcTextureParams = { -5, 20, 130, 130 };
            this->name = "rook";
            break; 

        case bishop :
            srcTextureParams = { 128, 20, 130, 130 };
            this->name = "bishop";
            break; 

        case knight :
            srcTextureParams = { 530, 20, 130, 130 };
            this->name = "knight";
            break; 

        case paw :
            srcTextureParams = { 670, 25, 120, 120 };
            this->name = "paw";
            break; 
    }

    switch(color) {
        case white :
            srcTextureParams.y += 160;
            this->colorStr = "white";
            break;
        
        case black : 
            this->colorStr = "black";
            break;

         case red : 
            this->colorStr = "red";
            break;

        case transparent : 
            this-> colorStr = "transparent";
            break;
    }

    destTextureParams = { SdlCore::getInstance()->size, SdlCore::getInstance()->size,  SdlCore::getInstance()->size, SdlCore::getInstance()->size };
}
 
Piece::~Piece() { 
    cleanup();
}

void Piece::setDestTextureParam() {
    destTextureParams.x = x * SdlCore::getInstance()->size;
    destTextureParams.y = y * SdlCore::getInstance()->size;
}

void Piece::up() {
    if(y >0) y--;
}

void Piece::down() {
    if(y <7) y++;
}

void Piece::left() {
    if(x >0) x--;
}

void Piece::right() {
    if(x <7) x++;
}

void Piece::display() {
    setDestTextureParam();
    SDL_RenderCopy(SdlCore::getInstance()->getRender(), SdlCore::getInstance()->getSdlTexture(), &srcTextureParams, &destTextureParams);
}

void Piece::cleanup() {
    //SDL_DestroyTexture(SdlCore::getInstance()->->getSdlTexture());
}
