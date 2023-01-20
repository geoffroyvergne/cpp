#include <iostream>
#include <piece.hpp>

#include "singleton_init.hpp"

Piece::Piece(PieceType pieceype) {
    //this->render = render;
    //this->sdl_texture = sdl_texture;

    //textureParams = { 120, 120,  90, 90 };
    //srcTextureParams = { 0, 0,  90, 90 };

    this->togglePieceType(pieceype);

    destTextureParams = { 120, 150,  90, 90 };
}

Piece::~Piece() {
    cleanup();
}

void Piece::togglePieceType(PieceType pieceype) {
    switch(pieceype) {
        case none : 
            srcTextureParams.x = 120;
            srcTextureParams.y = 89;
            srcTextureParams.w = 90;
            srcTextureParams.h = 90;

            this->pieceype = pieceype;
            this->name = "none";
            break;

        case rock : 
            srcTextureParams.x = 0;
            srcTextureParams.y = 97;
            srcTextureParams.w = 120;
            srcTextureParams.h = 120;

            this->pieceype = pieceype;
            this->name = "rock";
            break;

        case paper : 
            srcTextureParams.x = 0;
            srcTextureParams.y = 0;
            srcTextureParams.w = 100;
            srcTextureParams.h = 90;

            this->pieceype = pieceype;
            this->name = "paper";
            break;

        case sissors : 
            srcTextureParams.x = 100;
            srcTextureParams.y = 0;
            srcTextureParams.w = 120;
            srcTextureParams.h = 80;

            this->pieceype = pieceype;
            this->name = "sissors";
            break;
    }

    //std::string imagePath = "../assets/images-set.png";

    //if(sdl_texture != NULL) SDL_DestroyTexture(sdl_texture);
    //sdl_texture = IMG_LoadTexture(render, imagePath.c_str());
}

void Piece::nextPiece() {
    switch(pieceype) {
        case none : 
            togglePieceType(rock);             
            break;

        case rock : 
            togglePieceType(paper);             
            break;

        case paper : 
            togglePieceType(sissors);             
            break;

        case sissors : 
            togglePieceType(rock);             
            break;
    }
}

void Piece::randomPiece() {
    int piece = rand() % 3 + 1;

    switch(piece) {
        case 1 : 
            togglePieceType(rock);             
            break;

        case 2 : 
            togglePieceType(paper);             
            break;

        case 3 : 
            togglePieceType(sissors);             
            break;
    }
}

void Piece::display() {
    SDL_RenderCopy(SingletonInit::getInstance()->getRender(), SingletonInit::getInstance()->getSdlTexture(), &srcTextureParams, &destTextureParams);
}

void Piece::cleanup() {
    //SDL_DestroyTexture(sdl_texture);
}
