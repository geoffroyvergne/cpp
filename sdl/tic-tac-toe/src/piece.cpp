#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <piece.hpp>
#include <core.hpp>

Piece::Piece(PieceType pieceype) {
    srcTextureParams = { 30, 30,  90, 90 };
    destTextureParams = { 30, 30,  90, 90 };

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

void Piece::toggleColor() {
    //TODO Implement
}

void Piece::display() {
    SDL_RenderCopy(Core::getInstance()->getRender(), Core::getInstance()->getSdlTexture(), &srcTextureParams, &destTextureParams);
}

void Piece::moveUp() {
    if(destTextureParams.y >30) destTextureParams.y -= 180;
    caseNumberByTextureParams();
}

void Piece::moveDown() {
    if(destTextureParams.y <390) destTextureParams.y += 180;
    caseNumberByTextureParams();
}

void Piece::moveRight() {
    if(destTextureParams.x <390) destTextureParams.x += 180;
    caseNumberByTextureParams();
}


void Piece::moveLeft() {
    if(destTextureParams.x >30) destTextureParams.x -= 180;
    caseNumberByTextureParams();
}

void Piece::cleanup() {
    SDL_DestroyTexture(Core::getInstance()->getSdlTexture());
}

void Piece::caseNumberByTextureParams() {
    int caseNumber = 0;
    int rowNumber = 0;

    int rowArray[] = { 30, 210, 390 };
    int lineArray[] = { 30, 210, 390 };

    for(int row=0; row<3; row++) {
        rowNumber ++;
        int lineNumber = 0;
        for(int line=0; line<3; line++) {            
            caseNumber ++;
            lineNumber ++;

            if(this->destTextureParams.x == lineArray[line] && this->destTextureParams.y == rowArray[row]) {
                this->position = { caseNumber, rowNumber, lineNumber };
                
                return;         
            }
        }
    }
}
