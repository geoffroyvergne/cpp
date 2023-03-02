#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include <plateau.hpp>
#include <sdl-core.hpp>

#include <util.hpp>

Plateau::Plateau() {
    srcTextureParams = { 70, 139,  512, 460 };
    destTextureParams = { 11, 85,  512, 460 };

    clearPieceList();
}

Plateau::~Plateau() {
    cleanup();
}

void Plateau::clearPieceList() {    
    for(int i=0; i<6; i++) {
        for(int j=0; j<7; j++) {
            piece2dList[i][j] = new Piece(PieceType::none);
        }
    }
}

Piece* Plateau::addNewPiece(Piece *currentPiece) {    
    Piece *piece = new Piece(currentPiece->pieceType);
    piece->destTextureParams.x = currentPiece->destTextureParams.x;
    piece->destTextureParams.y = 429;
    piece->position.x = currentPiece->position.x;
    piece->position.y = 6;

    while(piece2dList[piece->position.y -1][piece->position.x -1]->player != Player::none) {
        piece->rowFull = piece->moveUp();
        if(piece->rowFull) break;
    }

    if(! piece->rowFull) {
        // add piece in 2d table at new position       
        this->piece2dList[piece->position.y -1][piece->position.x -1] = piece;
        this->displayTable();
        this->caseNumber(piece);       

        SDL_Log("piece->position.rowNumber %d piece->position.lineNumber %d countpiece %d caseNumber %d", piece->position.y -1, piece->position.x -1, countpiece(), piece->position.caseNumber);        
    }

    return piece;
}

void Plateau::displayPieces() {
    int pieceNumber = 0;
    for(std::array pieceList : piece2dList) {
        for(Piece* pieceInList : pieceList) {
            if(pieceInList->pieceType == PieceType::none) continue;
            pieceInList->display();
            pieceNumber++;
        }
    }
}

int Plateau::caseAlreadyUsed(Piece *piece) {    
    if(piece2dList[piece->position.y-1][piece->position.x-1]->pieceType != PieceType::none) return true;

    return false;
}

void Plateau::caseNumber(Piece *piece) {
    for(std::array pieceList : piece2dList) {
        for(Piece* pieceInList : pieceList) {
            piece->position.caseNumber++; 
            if(pieceInList->pieceType == PieceType::none) continue;
            if(pieceInList->position.x == piece->position.x && pieceInList->position.y == piece->position.y) return;
        }
    }
}

int Plateau::countRed() {
    int count = 0;
    for(std::array pieceList : piece2dList) {
        for(Piece* pieceInList : pieceList) {
            if(pieceInList->player == Player::red) {
                count ++;
            }
        }
    }

    return count;
}

int Plateau::countpiece() {
    int count = 0;
    for(std::array pieceList : piece2dList) {
        for(Piece* pieceInList : pieceList) {
            if(pieceInList->pieceType != PieceType::none) {
                count ++;
            }
        }
    }

    return count;
}

void Plateau::displayTable() {
     for(std::array pieceList : piece2dList) {
        for(Piece* pieceInList : pieceList) {
            std::cout << " " << Util::getPlayerInt(pieceInList->player);
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

/*

  1 2 3 4 5 6 7
1 0 0 0 0 0 0 0
2 0 0 0 0 0 0 0
3 0 0 0 0 0 0 0
4 0 0 0 0 0 0 0
5 0 0 0 0 0 0 0
6 0 0 0 0 0 0 0

*/

void Plateau::resetContainers() {
    columnCount = 0;
    rowCount = 0;
    regularDiagonalCount = 0;
    reverseDiagonalCount = 0;
}

Player Plateau::lineDone(Piece *piece) {
    int x = piece->position.x -1;
    int y = piece->position.y -1;

    int ymaxCase = 5;
    int xmaxCase = 6;

    int columnCount = 1;
    int rowCount = 1;
    int regularDiagonalCount = 1;
    int reverseDiagonalCount = 1;

    int checkNumber = 4;

    //if(casesUsed >=5) return none

    // lines Y
    // down : y+1q
    //if(y <maxCase) if(piece2dList[y+1][x]->player == player) columnCount ++;    
    for(int i=1; i<checkNumber; i++) {
        if(y+i > ymaxCase) break;
        if(piece2dList[y+i][x]->player == piece->player) { 
            columnCount ++;            
        } else break;
    }

    // rows X
    // left : x-1
    //if(x >0) if(piece2dList[y][x-1]->player == player) rowCount ++;    
    for(int i=1; i<checkNumber; i++) {
        if(x-i <0) break;
        if(piece2dList[y][x-i]->player == piece->player) {
            rowCount ++;
        } else break;
    }

    // right : x+1
    //if(x <ymaxCase) if(piece2dList[y][x+1]->player == player) rowCount ++;    
    for(int i=1; i<checkNumber; i++) {
        if(x+i >xmaxCase) break;
        if(piece2dList[y][x+i]->player == piece->player) {
            rowCount ++;
        } else break;
    }

    // regular diagonal
    // up -> right : y-1 -> x+1
    //if(y >0 && x <maxCase) { if(piece2dList[y-1][x+1]->player == player) regularDiagonalCount ++; }
    for(int i=1; i<checkNumber; i++) {
        if(y-i <0 || x+i >xmaxCase) break;
        if(piece2dList[y-i][x+i]->player == piece->player) {
            regularDiagonalCount ++;
        } else break;
    }

    // down -> left : y+1 -> x-1
    //if(y <maxCase && x >0) { if(piece2dList[y+1][x-1]->player == player) regularDiagonalCount ++; }
    for(int i=1; i<checkNumber; i++) {
        if(y+i >ymaxCase || x-i <0) break;
        if(piece2dList[y+i][x-i]->player == piece->player) {
            regularDiagonalCount ++;
        } else break;
    }

    // reverse diagonal

    // up -> left : y-1 -> x-1
    /*if(y >0 && x >0) {
        if(piece2dList[y-1][x-1]->player == player) reverseDiagonalCount ++;
    }*/
    for(int i=1; i<checkNumber; i++) {        
        if(y-i <0 || x-i <0) break;
        if(piece2dList[y-i][x-i]->player == piece->player) {
            reverseDiagonalCount ++;
        } else break;
    }

    // down -> right : y+1 -> x+1
    /*if(y <maxCase && x <maxCase) { 
        if(piece2dList[y+1][x+1]->player == player) reverseDiagonalCount ++;    
    }*/
    for(int i=1; i<checkNumber; i++) {        
        if(y+i >ymaxCase || x+i >xmaxCase) break;
        if(piece2dList[y+i][x+i]->player == piece->player) {
            reverseDiagonalCount ++;
        } else break;
    }

    SDL_Log("player %d rowCount x %d columnCount y %d regularDiagonalCount %d reverseDiagonalCount %d", piece->player, rowCount, columnCount, regularDiagonalCount, reverseDiagonalCount);    

    if(rowCount == checkNumber || columnCount == checkNumber || regularDiagonalCount == checkNumber || reverseDiagonalCount == checkNumber)
    return piece->player;

    /*if(rowCount == checkNumber) {
        SDL_Log("player %d win on row", piece->player);
        return piece->player;
    }

    if(columnCount == checkNumber) {
        SDL_Log("player %d win on column", piece->player);
        return piece->player;
    }

    if(regularDiagonalCount == checkNumber) {
        SDL_Log("player %d win on regular diagonal", piece->player);
        return piece->player;
    }

    if(reverseDiagonalCount == checkNumber) {
        SDL_Log("player %d win on reverse diagonal", piece->player);
        return piece->player;
    }*/

    return Player::none;
}

void Plateau::display() {
    SDL_RenderCopy(SdlCore::getInstance()->getRender(), SdlCore::getInstance()->getSdlTexture(), &srcTextureParams, &destTextureParams);
}

void Plateau::cleanup() {
    //SDL_DestroyTexture(Core::getInstance()->getSdlTexture());
}
