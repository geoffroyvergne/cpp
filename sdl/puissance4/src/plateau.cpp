#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include <plateau.hpp>
#include <core.hpp>

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
            piece2dList[i][j] = nullptr;
        }
    }
}

bool Plateau::addNewPiece(Piece *currentPiece) {    
    Piece *piece = new Piece(currentPiece->type);
    piece->destTextureParams.x = currentPiece->destTextureParams.x;
    piece->destTextureParams.y = 429;
    piece->position.x = currentPiece->position.x;
    piece->position.y = 6;

    int rowFull = false;    

    while(piece2dList[piece->position.y -1][piece->position.x -1] != nullptr) {
        rowFull = piece->moveUp();
        if(rowFull) break;
    }

    if(! rowFull) {
        // add piece in 2d table at new position       
        this->piece2dList[piece->position.y -1][piece->position.x -1] = piece;
        this->displayTable();
        this->caseNumber(piece);       

        SDL_Log("piece->position.rowNumber %d piece->position.lineNumber %d countpiece %d caseNumber %d", piece->position.y -1, piece->position.x -1, countpiece(), piece->position.caseNumber);

        this->lineDone(piece);
    }

    return rowFull;
}

void Plateau::displayPieces() {
    int pieceNumber = 0;
    for(std::array pieceList : piece2dList) {
        for(Piece* pieceInList : pieceList) {
            if(pieceInList == nullptr) continue;
            pieceInList->display();
            pieceNumber++;
        }
    }
}

int Plateau::caseAlreadyUsed(Piece *piece) {
    for(std::array pieceList : piece2dList) {
        for(Piece* pieceInList : pieceList) {
            if(pieceInList == nullptr) continue;
            if(piece->position.x == pieceInList->position.x && piece->position.y == pieceInList->position.y) return true;
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

int Plateau::countRed() {
    int count = 0;
    for(std::array pieceList : piece2dList) {
        for(Piece* pieceInList : pieceList) {
            if(pieceInList->player == red) {
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
            if(pieceInList != nullptr) {
                count ++;
            }
        }
    }

    return count;
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

// TODO Implement

/*

  1 2 3 4 5 6 7
1 0 0 0 0 0 0 0
2 0 0 0 0 0 0 0
3 0 0 0 0 0 0 0
4 0 0 0 0 0 0 0
5 0 0 0 0 0 0 0
6 0 0 0 0 0 0 0


      0
    0 0 0 0
      0
      0

*/

Player Plateau::lineDone(Piece *piece) {
    Player winner = player_none;
    
    int counterY = 1;
    int counterX = 1;

    int couterRegularDiagonal = 1;
    int couterReverseDiagonal = 1;
    
    int x = piece->position.x -1;
    int y = piece->position.y -1;

    SDL_Log("x %d y %d piece->position.rowNumber %d", x, y, piece2dList[y][x]->position.caseNumber);    

    // move right
    x = piece->position.x -1;
    y = piece->position.y -1;

    while(x<6) {
        x++;
        if(piece2dList[y][x] == nullptr) break;        
        else if(piece2dList[y][x]->player == piece->player) {
            counterX++;
        } else break;
    }

    // move left
    x = piece->position.x -1;
    y = piece->position.y -1;

    while(x>0) {
        x--;
        if(piece2dList[y][x] == nullptr) break;        
        else if(piece2dList[y][x]->player == piece->player) {
            counterX++;
        } else break;
    }
    
    //if(counterX == 4) return piece->player;

    // move down
    x = piece->position.x -1;
    y = piece->position.y -1;

    while(y<5) {
        y++;
        if(piece2dList[y][x]->player != piece->player) break;
        if(piece2dList[y][x]->player == piece->player) {
            counterY++;
        }
    }    

    //if(counterY == 4) return piece->player;

    // regular diagol up
    /*x = piece->position.x -1;
    y = piece->position.y -1;

    while(x<6 && y<=0) {
        x++; y--;
        if(piece2dList[y][x] == nullptr) break;
        if(piece2dList[y][x]->player != piece->player) break;
        if(piece2dList[y][x]->player == piece->player) {
            couterRegularDiagonal++;
        }
    }*/

    //regular diagonal down
    x = piece->position.x -1;
    y = piece->position.y -1;

    SDL_Log("x %d y %d", x, y);  

    while(x>0 && y<6) {
        x--; y++;
        SDL_Log("while x %d y %d", x, y);  
        if(piece2dList[y][x] == nullptr) break;
        if(piece2dList[y][x]->player != piece->player) break;
        if(piece2dList[y][x]->player == piece->player) {
            couterRegularDiagonal++;
        }
    }

    SDL_Log("player %d counterX %d counterY %d couterRegularDiagonal %d", piece->player, counterX, counterY, couterRegularDiagonal);  

    return winner;
}

void Plateau::display() {
    SDL_RenderCopy(Core::getInstance()->getRender(), Core::getInstance()->getSdlTexture(), &srcTextureParams, &destTextureParams);
}

void Plateau::cleanup() {
    //SDL_DestroyTexture(Core::getInstance()->getSdlTexture());
}
