#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include <plateau.hpp>
#include <piece.hpp>
#include <block.hpp>
#include <block-type.hpp>
#include <map>
#include <iterator>

Plateau::Plateau(SDL_Renderer *render) {
    this->render = render;   
    this->currentBlockType = base; 
    this->addWall();
}

Plateau::~Plateau() {
    cleanup();
}

int Plateau::detectCollision() {
    //TODO implement
    SDL_Rect pieceBloc;
    SDL_Rect wallBloc;
    SDL_bool collision;

    //this->collision = 0;
    //this->currentPiece->collision = 0;

    for (size_t i = 0; i < this->currentPiece->blockList.size(); ++i) {      
        pieceBloc = this->currentPiece->blockList[i]->textureParams;

        for (size_t j = 0; j < this->wallList.size(); ++j) {    
            wallBloc = this->wallList[j]->textureParams;
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

/*void Plateau::displayPieces() {
    for (size_t i = 0; i < this->pieceList.size(); ++i) {        
        this->pieceList[i]->display();
	}
}*/

void Plateau::addWall() {
    for(int i=0; i<15; i++) {
        Block *block = new Block(render, base);
        block->textureParams.x = 0;
        block->textureParams.y = (i+1) * 50;

        wallList.push_back(block);
    }

    for(int i=0; i<15; i++) {
        Block *block = new Block(render, base);
        block->textureParams.x = 500;
        block->textureParams.y = (i+1) * 50;

        wallList.push_back(block);
    }

    for(int i=0; i<9; i++) {
        Block *block = new Block(render, base);
        block->textureParams.x = (i+1) * 50;
        block->textureParams.y = 750;

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
    //this->currentBlockType=base;
}

void Plateau::addPiece() {
    Piece *piece = new Piece(this->render, this->currentBlockType);
    piece->blockList = this->currentPiece->blockList;
    piece->type = this->currentPiece->type;

    //this->pieceList.push_back(piece);
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
    for (auto wall : this->wallList) {
        delete wall;
    } 
    this->wallList.clear();
    this->addWall();
}

// if 9 blocks with the same y position, there is a line
// than remove all blocks with same y position
int Plateau::detectLineDone() {
    //int lineDone = 0;
    std::map<int, int> blockCount;

    for (size_t i = 0; i < this->wallList.size(); ++i) {
        //Do not count wall base blocks
        if(this->wallList[i]->type != base && this->wallList[i]->textureParams.y <= 2000) {
            int y = this->wallList[i]->textureParams.y;
            /*if(blockCount.find(y)->second == 8) {
                return y;                    
            }*/ 

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
        std::cout << it->first
                << ':'
                << it->second
               << std::endl;

        if(it->second == 9) return it->first;
    }

    return 0;
}

// TODO
void Plateau::removeLine(int lineDone) {
    //std::cout << lineDone << std::endl;
    for (size_t i = 0; i < this->wallList.size(); ++i) {
        if(this->wallList[i]->textureParams.y == lineDone && this->wallList[i]->type != base) {
            // remove this line
            this->wallList[i]->textureParams.y = 2000;
            
            //this->wallList.erase(this->wallList.begin() +i);
            //this->wallList.erase(std::remove(this->wallList.begin(), this->wallList.end(), this->wallList[i]), this->wallList.end());
            //this->wallList.shrink_to_fit();
            //this->wallList[i]->cleanup();
            //delete this->wallList[i];
        }
    }
}

// TODO
void Plateau::moveDownLine(int lineDone) {
    for (size_t i = 0; i < this->wallList.size(); ++i) {
        if(this->wallList[i]->textureParams.y != lineDone && this->wallList[i]->type != base) {
            this->wallList[i]->textureParams.y += 50;
        }
    }
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
