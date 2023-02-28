#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <plateau.hpp>
#include <core.hpp>

Plateau::Plateau() {
    srcTextureParams = { 87, 187,  512, 512 };
    destTextureParams = { 0, 0,  512, 512 };
    clearPieceList();
    resetContainers();
}

void Plateau::clearPieceList() {    
    for(int i=0; i<6; i++) {
        for(int j=0; j<7; j++) {
            piece2dList[i][j] = new Piece(piece_none);
        }
    }
}

void Plateau::display() {
    SDL_RenderCopy(Core::getInstance()->getRender(), Core::getInstance()->getSdlTexture(), &srcTextureParams, &destTextureParams);
}

Piece *Plateau::addCurrentPiece(Piece *lastCurrentPiece, Player player) {
    PieceType pieceType;
    if(player == cross) pieceType = red_cross;
    else if(player == circle) pieceType = red_circle;

    lastCurrentPiece->togglePlayer(pieceType);

    return lastCurrentPiece;
}

Player Plateau::addNewPiece(Piece *currentPiece, Player player) {
    PieceType pieceType;
    if(player == cross) pieceType = black_cross;
    else if(player == circle) pieceType = black_circle;

    Piece *piece = new Piece(pieceType);
    piece->destTextureParams.x = currentPiece->destTextureParams.x;
    piece->destTextureParams.y = currentPiece->destTextureParams.y;
    piece->position.x = currentPiece->position.x;
    piece->position.y = currentPiece->position.y;

    // add piece in 2d table at new position
    this->piece2dList[piece->position.y-1][piece->position.x-1] = piece;

    this->caseNumber(piece);

    SDL_Log("piece->position.rowNumber %d piece->position.lineNumber %d countpiece %d caseNumber %d", piece->position.y -1, piece->position.x -1, countpiece(), piece->position.caseNumber);

    return this->checkWin(piece);
}

void Plateau::displayPieces() {
    for(std::array pieceList : piece2dList) {
        for(Piece* pieceInList : pieceList) {
            if(pieceInList->pieceType == piece_none) continue;
            pieceInList->display();
        }
    }
}

int Plateau::caseAlreadyUsed(Piece *piece) {
    if(piece2dList[piece->position.y-1][piece->position.x-1]->pieceType != piece_none) return true;

    return false;
}

void Plateau::caseNumber(Piece *piece) {
    for(std::array pieceList : piece2dList) {
        for(Piece* pieceInList : pieceList) {
            piece->position.caseNumber++; 
            if(pieceInList->pieceType == piece_none) continue;
            if(pieceInList->position.x == piece->position.x && pieceInList->position.y == piece->position.y) return;
        }
    }
}

void Plateau::displayTable() {
    for(std::array pieceList : piece2dList) {
        for(Piece* pieceInList : pieceList) {
            std::cout << " " << pieceInList->pieceType;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int Plateau::countpiece() {
    int count = 0;
    for(std::array pieceList : piece2dList) {
        for(Piece* pieceInList : pieceList) {
            if(pieceInList->pieceType != piece_none) {
                count ++;
            }
        }
    }

    return count;
}

void Plateau::resetContainers() {
    /*int boardSize = 3;
    for(int i=0; i<boardSize; i++) {
        for(int j=0; j<boardSize; j++) {
            rowContainer[i][j] = 0;
            columnContainer[i][j] = 0;
            regularDiagonalContainer[i][j] = 0;
            oppositDiagonalContainer[i][j] = 0;
        }
    }*/

    columnCount = 0;
    rowCount = 0;
    regularDiagonalCount = 0;
    reverseDiagonalCount = 0;
}

/*
1 2 3
4 5 6
7 8 9

  1 2 3
1 0 0 0
2 0 0 0
3 0 0 0

*/

Player Plateau::checkWin(Piece *piece) {
    int x = piece->position.x -1;
    int y = piece->position.y -1;
    Player player = piece->player;

    int maxCase = 2;

    //if(casesUsed >=5) return none

    // lines
    // up : y-1
    if(y >0) if(piece2dList[y-1][x]->player == player) columnCount ++;
    // down : y+1         
    if(y <maxCase) if(piece2dList[y+1][x]->player == player) columnCount ++;

    // rows
    // left : x-1
    if(x >0) if(piece2dList[y][x-1]->player == player) rowCount ++;
    // right : x+1
    if(x <maxCase) if(piece2dList[y][x+1]->player == player) rowCount ++;

    // regular diagonal
    // up -> right : y-1 -> x+1
    if(y >0 && x <maxCase) {
        if(piece2dList[y-1][x+1]->player == player) regularDiagonalCount ++;
    }

    // down -> left : y+1 -> x-1
    if(y <maxCase && x >0) {
        if(piece2dList[y+1][x-1]->player == player) regularDiagonalCount ++;
    }

    // reverse diagonal
    // up -> left : y-1 -> x-1
    if(y >0 && x >0) {
        if(piece2dList[y-1][x-1]->player == player) reverseDiagonalCount ++;
    }
    
    // down -> right : y+1 -> x+1
    if(y <maxCase && x <maxCase) { 
        if(piece2dList[y+1][x+1]->player == player) reverseDiagonalCount ++;    
    }

    SDL_Log("rowCount %d columnCount %d regularDiagonalCount %d reverseDiagonalCount %d", rowCount, columnCount, regularDiagonalCount, reverseDiagonalCount);    

    if(rowCount == 3 || columnCount == 3 || regularDiagonalCount == 3 || reverseDiagonalCount == 3) return player;
    else return none;
}

// https://jayeshkawli.ghost.io/tic-tac-toe/
// tic tac toe win check algorithme
//Player Plateau::checkWin(Piece *piece, int boardSize) {
    /*int row = piece->position.x;
    int column = piece->position.y;
    Player player = piece->player;

    SDL_Log("player %d row %d column %d", player, row, column);    
    
    rowContainer[player][row] +=1;
    columnContainer[player][column] +=1;        

    if(row == column) {
        regularDiagonalContainer[player][row] ++;
    }

    if(row + column + 1 == boardSize) {
        oppositDiagonalContainer[player][row] ++;
    }

    if(rowContainer[player][row] == boardSize) {
        SDL_Log("Win accross row !");
        //resetContainers(boardSize);
        return player;
    }

    if(columnContainer[player][column] == boardSize) {
        SDL_Log("Win accross column !");
        //resetContainers(boardSize);
        return player;
    }

    int sumForRegularDiagonalElement = 0;
    int sumForOppositDiagonalElement = 0;

    for(int i=0; i<boardSize; i++) {
        sumForRegularDiagonalElement += regularDiagonalContainer[player][i];
        sumForOppositDiagonalElement += oppositDiagonalContainer[player][i]; 
    }

    if(sumForRegularDiagonalElement == boardSize) {
        SDL_Log("Win accross regular diagonal !");
        //resetContainers(boardSize);
        return player;
    }

    if(sumForOppositDiagonalElement == boardSize) {
        SDL_Log("Win accross opposit diagonal !");
        //resetContainers(boardSize);
        return player;
    }

    return none;*/
//}

