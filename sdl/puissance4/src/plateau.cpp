#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include <plateau.hpp>
#include <core.hpp>

Plateau::Plateau() {
    srcTextureParams = { 70, 139,  512, 460 };
    destTextureParams = { 11, 85,  512, 460 };
}

Plateau::~Plateau() {
    cleanup();
}

void Plateau::displayPieces() {
    /*for (size_t i = 0; i < this->pieceList.size(); ++i) {
        this->pieceList[i]->display();
	}*/

    for(Piece* piece : pieceList) {
        piece->display();
    }
}

int Plateau::addNewPiece(Piece *currentPiece) {    
    Piece *piece = new Piece(currentPiece->type);
    piece->destTextureParams.x = currentPiece->destTextureParams.x;
    piece->destTextureParams.y = 429;

    int rowFull = false;
    
    while(caseAlreadyUsed(piece)) {
        rowFull = piece->moveUp();
        if(rowFull) break;
    }

    int caseNumber = getCaseNumberByTextureParams(piece);

    if(! rowFull) {
        //pieceList.push_back(piece);
        //pieceList.insert(pieceList.begin() + piece->caseNumber, piece); 

        if(pieceList.empty()){
            pieceList.push_back(piece);    
        } else {
            pieceList.insert(pieceList.begin(), caseNumber, piece);
        }
    } 

    return rowFull;
}

int Plateau::caseAlreadyUsed(Piece *piece) {
     //for (size_t i = 0; i < this->pieceList.size(); ++i) {
    for(Piece* pieceInList : pieceList) {        
         if(piece->destTextureParams.x == pieceInList->destTextureParams.x && piece->destTextureParams.y == pieceInList->destTextureParams.y) {
             return true;
         }
     }

     return false;
}

int Plateau::getCaseNumberByTextureParams(Piece *piece) {
    /*
(+67)
lines   26   93   160  227  294  361  428
    -1  -07  -06  -05  -04  -03  -02  -01  2
    0   00   01   02   03   04   05   06   69
    1   07   08   09   10   11   12   13   141
    2   14   15   16   17   18   19   20   213
    3   21   22   23   24   25   26   27   285
    4   28   29   30   31   32   33   34   357
    5   35   36   37   38   39   40   41   429
        0    1    2    3    4    5    6   rows (+72)
    */
    //00 = 26 69
    //35 = 26 429
    //36 = 93 429

    //41 = 428 429

    //lines x67
    //first line : 69
    //last line : 428

    //rows x72
    //first row : 26
    //last row : 428

    int caseNumber = 0;
    int rowNumber = 0;
    int lineNumber = 0;

    int rowArray[] = { 89, 157, 225, 293, 361, 429 };
    int lineArray[] = { 17, 84, 151, 218, 285, 352, 419 };
    //int lineArray[] = { 26, 93, 160, 227, 294, 361, 428 };

    //SDL_Log("piece->destTextureParams.x %d piece->destTextureParams.y %d", piece->destTextureParams.x, piece->destTextureParams.y);

    for(int row=0; row<6; row++) {
        rowNumber ++;
        int lineNumber = 0;

        for(int line=0; line<7; line++) {
            //SDL_Log("lineArray[line] %d rowArray[row] %d ", lineArray[line], rowArray[row]);
            
            lineNumber ++;

            if(piece->destTextureParams.x == lineArray[line] && piece->destTextureParams.y == rowArray[row]) {
                piece->position = { caseNumber, rowArray[row], lineArray[line] };
                piece->caseNumber = caseNumber;

                SDL_Log("caseNumber %d rowNumber %d lineNumber %d ", caseNumber, rowNumber, lineNumber);

                return caseNumber;          
            }
            caseNumber++;
        }
    }

    return caseNumber;

    //SDL_Log("destTextureParams.x %d destTextureParams.y %d", piece->destTextureParams.x, piece->destTextureParams.y);
    //SDL_Log("Case Number %d", piece->caseNumber);
}

int Plateau::vectorContains(int caseNumber, Player player) {
    for(Piece* piece : pieceList) {
        if(piece->caseNumber == (caseNumber) && piece->player == player) {
            return true;
        }
    }

    return false;
}

Player Plateau::lineDone(Player currentPlayer) {
    Player winner = player_none;

    /*
    0   00   01   02   03   04   05   06
    1   07   08   09   10   11   12   13
    2   14   15   16   17   18   19   20
    3   21   22   23   24   25   26   27
    4   28   29   30   31   32   33   34
    5   35   36   37   38   39   40   41
        0    1    2    3    4    5    6   
    */

   if(pieceList.size() >= 3) {
        int linecheck[48][4] = {
            {0,1,2,3}, {1,2,3,4}, {2,3,4,5}, {3,4,5,6}, // horizontale 1
            {}, {}, {}, {}, // horizontale 2
            {}, {}, {}, {}, // horizontale 3
            {}, {}, {}, {}, // horizontale 4
            {35,36,37,38}, {}, {}, {}, // horizontale 5
            {0,7,14,21}, {7,14,21,28}, {14,21,28,35}, // verticale 1
            {}, {}, {}, {}, // verticale 2
            {}, {}, {}, {}, // verticale 3
            {}, {}, {}, {}, // verticale 4
            {}, {}, {}, {}, // verticale 5
            {}, {}, {}, {}, // verticale 6
            {}, {}, {}, {}, // verticale 7
        };
        
        for (int i=0; i<48; i++) {
            if(
                vectorContains(linecheck[i][0], currentPlayer) && 
                vectorContains(linecheck[i][1], currentPlayer) && 
                vectorContains(linecheck[i][2], currentPlayer) && 
                vectorContains(linecheck[i][3], currentPlayer)                
            ) 
            {
                SDL_Log("Winner %u", currentPlayer);
                return currentPlayer;
            }
        }
    }

    return winner;
}

void Plateau::display() {
    SDL_RenderCopy(Core::getInstance()->getRender(), Core::getInstance()->getSdlTexture(), &srcTextureParams, &destTextureParams);
}

void Plateau::cleanup() {
    //SDL_DestroyTexture(Core::getInstance()->getSdlTexture());
}

