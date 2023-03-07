#include <iostream>
#include <piece.hpp>

#include <sdl-core.hpp>

Piece::Piece(PieceType pieceype) {
    this->togglePieceType(pieceype);
    destTextureParams = { 120, 150,  90, 90 };
}

Piece::~Piece() {
    cleanup();
}

void Piece::togglePieceType(PieceType pieceype) {
    switch(pieceype) {
        case PieceType::none : 
            srcTextureParams.x = 120;
            srcTextureParams.y = 89;
            srcTextureParams.w = 90;
            srcTextureParams.h = 90;

            this->pieceype = pieceype;
            this->name = "none";
            break;

        case PieceType::rock : 
            srcTextureParams.x = 0;
            srcTextureParams.y = 97;
            srcTextureParams.w = 120;
            srcTextureParams.h = 120;

            this->pieceype = pieceype;
            this->name = "rock";
            break;

        case PieceType::paper : 
            srcTextureParams.x = 0;
            srcTextureParams.y = 0;
            srcTextureParams.w = 100;
            srcTextureParams.h = 90;

            this->pieceype = pieceype;
            this->name = "paper";
            break;

        case PieceType::sissors : 
            srcTextureParams.x = 100;
            srcTextureParams.y = 0;
            srcTextureParams.w = 120;
            srcTextureParams.h = 80;

            this->pieceype = pieceype;
            this->name = "sissors";
            break;
    }
}

void Piece::nextPiece() {
    switch(pieceype) {
        case PieceType::none : 
            togglePieceType(PieceType::rock);             
            break;

        case PieceType::rock : 
            togglePieceType(PieceType::paper);             
            break;

        case PieceType::paper : 
            togglePieceType(PieceType::sissors);             
            break;

        case PieceType::sissors : 
            togglePieceType(PieceType::rock);             
            break;
    }
}

void Piece::randomPiece() {
    int piece = rand() % 3 + 1;

    switch(piece) {
        case 1 : 
            togglePieceType(PieceType::rock);             
            break;

        case 2 : 
            togglePieceType(PieceType::paper);             
            break;

        case 3 : 
            togglePieceType(PieceType::sissors);             
            break;
    }
}

void Piece::display() {
    SDL_RenderCopy(SdlCore::getInstance()->getRender(), SdlCore::getInstance()->getSdlTexture(), &srcTextureParams, &destTextureParams);
}

void Piece::cleanup() {
    //SDL_DestroyTexture(sdl_texture);
}
