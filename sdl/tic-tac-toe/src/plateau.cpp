#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <plateau.hpp>
#include <core.hpp>

Plateau::Plateau() {
    srcTextureParams = { 87, 187,  512, 512 };
    destTextureParams = { 0, 0,  512, 512 };
}

void Plateau::display() {
    SDL_RenderCopy(Core::getInstance()->getRender(), Core::getInstance()->getSdlTexture(), &srcTextureParams, &destTextureParams);
}

int Plateau::caseAlreadyUsed(Piece *piece) {
    for(Piece* pieceInList : pieceList) {
        if(piece->destTextureParams.x == pieceInList->destTextureParams.x && piece->destTextureParams.y == pieceInList->destTextureParams.y) {
            return true;
        }
    }

    return false;
}

void Plateau::displayPieces() {
    for(Piece* pieceInList : pieceList) {
        pieceInList->display();
    }
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

    int caseNumber = getCaseNumberByTextureParams(piece);
    
    piece->caseNumber = caseNumber;

    /*SDL_Log("caseNumber %d", caseNumber);
    SDL_Log("currentPiece->destTextureParams.x %d", currentPiece->destTextureParams.x);
    SDL_Log("currentPiece->destTextureParams.y %d", currentPiece->destTextureParams.y);*/

    if(pieceList.empty()){
        pieceList.push_back(piece);    
    } else {
        pieceList.insert(pieceList.begin(), caseNumber+1, piece);
    }

    //pieceList.push_back(piece);

    return this->lineDone(player);
}

int Plateau::getCaseNumberByTextureParams(Piece *piece) {
    int caseNumber = 0;
    int rowNumber = 0;
    
    /*{1,2,3},    
    {4,5,6},
    {7,8,9},*/

    int rowArray[] = { 30, 210, 390 };
    int lineArray[] = { 30, 210, 390 };

    for(int row=0; row<3; row++) {
        rowNumber ++;
        int lineNumber = 0;
        for(int line=0; line<3; line++) {
            
            caseNumber ++;
            lineNumber ++;

            if(piece->destTextureParams.x == lineArray[line] && piece->destTextureParams.y == rowArray[row]) {
                //piece->position = { caseNumber, rowArray[row], lineArray[line] };

                piece->position = { caseNumber, rowArray[row], lineArray[line] };
                piece->caseNumber = caseNumber;

                //SDL_Log("lineArray[line] %d rowArray[row] %d ", lineArray[line], rowArray[row]);
                SDL_Log("caseNumber %d rowNumber %d lineNumber %d ", caseNumber, rowNumber, lineNumber);

                return caseNumber;                
            }
        }
    }

    return caseNumber;
}

int Plateau::vectorContains(int caseNumber, Player player) {
    for(Piece* piece : pieceList) {
        if(piece->caseNumber == (caseNumber+1) && piece->player == player) {
            return true;
        }
    }

    return false;
}

/*

{1,2,3},
{4,5,6},
{7,8,9},

{0-0,0-1,0-2},
{1-0,1-1,1-2},
{2-0,2-1,2-2},

horizontal
1 2 3
4 5 6
7 8 9

verticale
1 4 7
2 5 8
3 6 9

diagonale
1 3 9
3 5 7

1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9

  1   2   3
1 1 | 2 | 3
2 4 | 5 | 6
3 7 | 8 | 9

X | 2 | 3
4 | X | 6
7 | 8 | X

*/

Player Plateau::lineDone(Player currentPlayer) {

    /*
    1 2 3
    4 5 6
    7 8 9

    0 1 2
    3 4 5
    6 7 8
    */

    if(pieceList.size() >= 3) {
        int linecheck[8][3] = {
            {0,1,2}, {3,4,5}, {6,7,8}, // horizontales
            {0,3,6}, {1,4,7}, {2,5,8}, // verticales
            {0,4,8}, {2,4,6} // diagonales
        };
        
        for (int i=0; i<8; i++) {
            if(
                vectorContains(linecheck[i][0], currentPlayer) && 
                vectorContains(linecheck[i][1], currentPlayer) &&                 
                vectorContains(linecheck[i][2], currentPlayer)
            ) return currentPlayer;
        }
    }

    return none;
}
