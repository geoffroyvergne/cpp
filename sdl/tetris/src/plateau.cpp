#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <stdlib.h>

#include <plateau.hpp>
#include <piece.hpp>
#include <block.hpp>
#include <block-type.hpp>
#include <map>
#include <iterator>
#include <core.hpp>

Plateau::Plateau() {
    this->currentBlockType = base; 
    this->addWall();
}

Plateau::~Plateau() {
    Core::getInstance()->cleanup();
}

int Plateau::detectCollision() {
    SDL_Rect pieceBloc;
    SDL_Rect wallBloc;
    SDL_bool collision;

    //this->collision = 0;
    //this->currentPiece->collision = 0;

    for (size_t i = 0; i < this->currentPiece->blockList.size(); ++i) {      
        pieceBloc = this->currentPiece->blockList[i]->destTextureParams;

        for (size_t j = 0; j < this->wallList.size(); ++j) {    
            wallBloc = this->wallList[j]->destTextureParams;
            collision = SDL_HasIntersection(&pieceBloc, &wallBloc);
            if (collision) {
                //this->collision = 1;
                //this->currentPiece->collision = 1;
                //SDL_Log("collision detected");
                return true;
            } /*else {
                this->collision = 0;
                this->currentPiece->collision = 0;
            }*/
        }
    }

    return false;
}

void Plateau::addWall() {
    for(int i=0; i<15; i++) {
        Block *block = new Block(base);
        block->destTextureParams.x = 0;
        block->destTextureParams.y = (i+1) * 50;

        wallList.push_back(block);
    }

    for(int i=0; i<15; i++) {
        Block *block = new Block(base);
        block->destTextureParams.x = 500;
        block->destTextureParams.y = (i+1) * 50;

        wallList.push_back(block);
    }

    for(int i=0; i<9; i++) {
        Block *block = new Block(base);
        block->destTextureParams.x = (i+1) * 50;
        block->destTextureParams.y = 750;

        wallList.push_back(block);
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
}

void Plateau::randomBlockType() {
    int value = rand() % 7 + 1;

    switch(value) {
        case 1 : 
            this->currentBlockType=I;
            break;

        case 2 : 
            this->currentBlockType=Z;
            break;

        case 3 : 
            this->currentBlockType=L;
            break;

        case 4 : 
            this->currentBlockType=J;
            break;

        case 5 : 
            this->currentBlockType=T;
            break;

        case 6 : 
            this->currentBlockType=S;
            break;

        case 7 : 
            this->currentBlockType=O;
            break;

        case 8 : 
            this->currentBlockType=I;
            break;
    }
}

void Plateau::addPiece() {
    Piece *piece = new Piece(this->currentBlockType);
    piece->blockList = this->currentPiece->blockList;
    piece->type = this->currentPiece->type;
}

void Plateau::displayCurrentPiece() {
    currentPiece->display();
}

void Plateau::addCurrentPiece() {
    //toggleBlockType();
    randomBlockType();
    if(currentPiece == NULL) delete currentPiece;
    currentPiece = new Piece(this->currentBlockType);
    //SDL_Log("this->currentBlockType : %d", this->currentBlockType);
}

void Plateau::rotateCurrentPieceToPreviousPosition() {
    this->currentPiece->previousPosition();

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

void Plateau::resetWall() {

    this->wallList.clear();
    this->addWall();
    
    /*for (auto wall : this->wallList) {
        delete wall;
    }*/

    //TODO fixe it
    /*int erased = 0;

    for(int i=0; i<5; i++) {
        for (size_t i = 0; i < this->wallList.size(); ++i) {
            if(this->wallList[i]->type != base) {
                //this->wallList[i]->cleanup();
                this->wallList.erase(this->wallList.begin() + i);
            }
        }
    }*/
}

// if 9 blocks with the same y position, there is a line
// than remove all blocks with same y position
int Plateau::detectLineDone() {    
    std::map<int, int> blockCount;

    for (size_t i = 0; i < this->wallList.size(); ++i) {
        //Do not count wall base blocks
        if(this->wallList[i]->type != base && this->wallList[i]->destTextureParams.y < 2000) {
            int y = this->wallList[i]->destTextureParams.y;
            
            //SDL_Log("blockCount");
            if (blockCount.count(y) > 0) {
                //SDL_Log("blockCount.find(y)->second %d", blockCount.find(y)->second);
                
                blockCount.insert({ y, (blockCount.find(y)->second ++) });
            } else {
                blockCount.insert({ y, 1 });
            }
        }
    }

    std::map<int, int>::iterator it;

    for (it = blockCount.begin(); it != blockCount.end(); it++) {        
        if(it->second == 9) return it->first;
    }

    return 0;
}

// TODO remove properly blocks instead of moving them
void Plateau::removeLine(int lineDone) {
    //TODO fixe it
    for(int i=0; i<5; i++) {
        for (size_t i = 0; i < this->wallList.size(); ++i) {
            if(this->wallList[i]->destTextureParams.y == lineDone && this->wallList[i]->type != base) {
                // move up this line
                //this->wallList[i]->cleanup();
                this->wallList[i]->destTextureParams.y = 2000;            
                this->wallList.erase(this->wallList.begin() + i);
            }
        }
    }
}

void Plateau::moveDownLine(int lineDone) {
    for (size_t i = 0; i < this->wallList.size(); ++i) {
        if(this->wallList[i]->type != base) {
            if(this->wallList[i]->destTextureParams.y <= lineDone && this->wallList[i]->destTextureParams.y <800) {
                this->wallList[i]->destTextureParams.y += 50;
            }
        }
    }
}

int Plateau::gameOver() {
    for (size_t i = 0; i < this->wallList.size(); ++i) {
        if(this->wallList[i]->destTextureParams.y <200 && this->wallList[i]->type != base) {
            return 1;
        }
    }
    return 0;   
}

void Plateau::display() {
    for (size_t i = 0; i < this->wallList.size(); ++i) {
        this->wallList[i]->display();
    }
}

void Plateau::cleanup() {
    for (size_t i = 0; i < this->wallList.size(); ++i) {
        this->wallList[i]->cleanup();
    }
}
