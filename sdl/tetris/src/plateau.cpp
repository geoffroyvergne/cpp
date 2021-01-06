#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include <plateau.hpp>
#include <piece.hpp>
#include <block.hpp>
#include <block-type.hpp>

Plateau::Plateau(SDL_Renderer *render) {
    this->render = render;   
    this->currentBlockType = base; 
}

Plateau::~Plateau() {
    cleanup();
}

void Plateau::displayPieces() {
    for (size_t i = 0; i < this->pieceList.size(); ++i) {        
        this->pieceList[i]->display();
	}
}

void Plateau::toggleBlockType() {
    //SDL_Log("this->currentBlockType : %d", this->currentBlockType);
    switch(this->currentBlockType) {
        case base : 
            this->currentBlockType=I;
            break;

        case I : 
            this->currentBlockType=Z;
            break;

        case Z : 
            this->currentBlockType=L;
            break;

        case L : 
            this->currentBlockType=J;
            break;

        case J : 
            this->currentBlockType=T;
            break;

        case T : 
            this->currentBlockType=S;
            break;

        case S : 
            this->currentBlockType=O;
            break;

        case O : 
            this->currentBlockType=I;
            break;
    }
    //this->currentBlockType=base;
}

void Plateau::addPiece() {
    Piece *piece = new Piece(this->render, this->currentBlockType);
    piece->blockList = this->currentPiece->blockList;
    piece->type = this->currentPiece->type;

    this->pieceList.push_back(piece);
}

void Plateau::displayCurrentPiece() {
    currentPiece->display();
}

void Plateau::addCurrentPiece() {
    toggleBlockType();
    if(currentPiece == NULL) delete currentPiece;
    currentPiece = new Piece(this->render, this->currentBlockType);
    //SDL_Log("this->currentBlockType : %d", this->currentBlockType);
}

void Plateau::rotateCurrentPiece() {
    this->currentPiece->nextPosition();

    switch(this->currentBlockType) {
        case base : 
            
            break;

        case I : 
            this->currentPiece->rotateI(currentBlockType);
            break;
        case Z : 
            this->currentPiece->rotateZ(currentBlockType);
            break;
        case L : 
            this->currentPiece->rotateL(currentBlockType);
            break;
        case J : 
            this->currentPiece->rotateJ(currentBlockType);
            break;
        case T : 
            this->currentPiece->rotateT(currentBlockType);
            break;
        case S : 
            this->currentPiece->rotateS(currentBlockType);
            break;
        case O : 
            this->currentPiece->rotateO(currentBlockType);
            break;
    }
}

void Plateau::display() {

}

void Plateau::cleanup() {

}
