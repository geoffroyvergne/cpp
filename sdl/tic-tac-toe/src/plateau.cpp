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
}

void Plateau::clearPieceList() {    
    for(int i=0; i<6; i++) {
        for(int j=0; j<7; j++) {
            piece2dList[i][j] = nullptr;
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

    return this->checkWin(piece->player, piece->position.x -1, piece->position.y -1, 3);
}

void Plateau::displayPieces() {
    for(std::array pieceList : piece2dList) {
        for(Piece* pieceInList : pieceList) {
            if(pieceInList == nullptr) continue;
            pieceInList->display();
        }
    }
}

int Plateau::caseAlreadyUsed(Piece *piece) {
    for(std::array pieceList : piece2dList) {
        for(Piece* pieceInList : pieceList) {
            if(pieceInList == nullptr) continue;            

            if(piece->position.caseNumber == pieceInList->position.caseNumber) {
                return true;
            }
        }
    }

    return false;
}

void Plateau::caseNumber(Piece *piece) {
    for(std::array pieceList : piece2dList) {
        for(Piece* pieceInList : pieceList) {
            piece->position.caseNumber++; 
            if(pieceInList == nullptr) continue;    
            if(pieceInList->position.x == piece->position.x && pieceInList->position.y == piece->position.y) return;
        }
    }
}

void Plateau::displayTable() {
    for(std::array pieceList : piece2dList) {
        for(Piece* pieceInList : pieceList) {
            if(pieceInList == nullptr) std::cout << " " << "0";
            else std::cout << " " << pieceInList->player;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int Plateau::countpiece() {
    int count = 0;
    for(std::array pieceList : piece2dList) {
        for(Piece* pieceInList : pieceList) {
            if(pieceInList != nullptr) {
                count ++;
            }
        }
    }

    return count;
}

void Plateau::resetContainers(int boardSize) {
    for(int i=0; i<2; i++) {
        for(int j=0; j<boardSize; j++) {
            rowContainer[i][j] = 0;
            columnContainer[i][j] = 0;
            regularDiagonalContainer[i][j] = 0;
            oppositDiagonalContainer[i][j] = 0;
        }
    }
}

// https://jayeshkawli.ghost.io/tic-tac-toe/
// tic tac toe win check algorithme
Player Plateau::checkWin(Player player, int row, int column, int boardSize) {
    int playerNumber = player;

    rowContainer[playerNumber][row] +=1;
    columnContainer[playerNumber][column] +=1;

    if(row == column) {
        regularDiagonalContainer[playerNumber][row] +=1;
    }

    if(row + column + 1 == boardSize) {
        oppositDiagonalContainer[playerNumber][row] += 1;
    }

    if(rowContainer[playerNumber][row] == boardSize) {
        SDL_Log("Win accross row !");
        resetContainers(boardSize);
        return player;
    }

    if(columnContainer[playerNumber][column] == boardSize) {
        SDL_Log("Win accross column !");
        resetContainers(boardSize);
        return player;
    }

    int sumForRegularDiagonalElement = 0;
    int sumForOppositDiagonalElement = 0;

    for(int i=0; i<boardSize; i++) {
        sumForRegularDiagonalElement += regularDiagonalContainer[playerNumber][i];
        sumForOppositDiagonalElement += oppositDiagonalContainer[playerNumber][i]; 
    }

    if(sumForRegularDiagonalElement == boardSize) {
        SDL_Log("Win accross regular diagonal !");
        resetContainers(boardSize);
        return player;
    }

    if(sumForOppositDiagonalElement == boardSize) {
        SDL_Log("Win accross opposit diagonal !");
        resetContainers(boardSize);
        return player;
    }

    return none;
}

