#include <iostream>
#include <piece.hpp>

Piece::Piece(SDL_Renderer *render, PieceType pieceype) {
    this->render = render;
    textureParams = { 120, 120,  90, 90 };

    this->togglePieceType(pieceype);
}

Piece::~Piece() {
    cleanup();
}

void Piece::togglePieceType(PieceType pieceype) {
    switch(pieceype) {
        case none : 
            imagePath = "../assets/question-mark.png";
            this->pieceype = pieceype;
            this->name = "none";
            break;

        case rock : 
            imagePath = "../assets/rock.png";             
            this->pieceype = pieceype;
            this->name = "rock";
            break;

        case paper : 
            imagePath = "../assets/paper.png";
            this->pieceype = pieceype;
            this->name = "paper";
            break;

        case sissors : 
            imagePath = "../assets/sissors.png";
            this->pieceype = pieceype;
            this->name = "sissors";
            break;
    }

    if(sdl_texture != NULL) SDL_DestroyTexture(sdl_texture);
    sdl_texture = IMG_LoadTexture(render, imagePath.c_str());
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
    SDL_RenderCopy(render, sdl_texture, NULL, &textureParams);
}

void Piece::cleanup() {
    SDL_DestroyTexture(sdl_texture);
}