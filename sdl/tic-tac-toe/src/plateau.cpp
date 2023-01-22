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
     for (size_t i = 0; i < this->pieceList.size(); ++i) {
         if(piece->destTextureParams.x == this->pieceList[i]->destTextureParams.x && piece->destTextureParams.y == this->pieceList[i]->destTextureParams.y) {
             return true;
         }
     }

     return false;
}

void Plateau::displayPieces() {
    for (size_t i = 0; i < this->pieceList.size(); ++i) {
        this->pieceList[i]->display();
	}
}

Piece *Plateau::addCurrentPiece(Piece *lastCurrentPiece, Player player) {
    PieceType pieceType;
    if(player == cross) pieceType = red_cross;
    else if(player == circle) pieceType = red_circle;

    //SDL_DestroyTexture(lastCurrentPiece->sdl_texture);
    lastCurrentPiece->togglePlayer(pieceType);

    //Piece *piece = new Piece(render, pieceType);
    //piece->textureParams.x = lastCurrentPiece->textureParams.x;
    //piece->textureParams.y = lastCurrentPiece->textureParams.y;

    //lastCurrentPiece->type = pieceType;

    //delete piece;

    return lastCurrentPiece;
}

Player Plateau::addNewPiece(Piece *currentPiece, Player player) {
    PieceType pieceType;
    if(player == cross) pieceType = black_cross;
    else if(player == circle) pieceType = black_circle;

    Piece *piece = new Piece(pieceType);
    piece->destTextureParams.x = currentPiece->destTextureParams.x;
    piece->destTextureParams.y = currentPiece->destTextureParams.y;
    
    //piece->setCaseNumberByTextureParams();
    //SDL_Log("Case Number %d", piece->caseNumber);

    //SDL_Log("Case Number %d", getCaseNumberByTextureParams(currentPiece));

    //SDL_Log("srcTextureParams.x %d", piece->destTextureParams.x);
    //SDL_Log("srcTextureParams.y %d", piece->destTextureParams.y);

    int caseNumber = getCaseNumberByTextureParams(piece->destTextureParams.x, piece->destTextureParams.y);
    piece->caseNumber = caseNumber;

    //SDL_Log("srcTextureParams.x %d", piece->destTextureParams.x);
    //SDL_Log("srcTextureParams.y %d", piece->destTextureParams.y);
    SDL_Log("caseNumber %d", caseNumber);

    pieceList.push_back(piece);

    return this->lineDone();
}

int Plateau::getCaseNumberByTextureParams(int x, int y) {
    // 30 210 390

    if(x == 30 && y == 30) {
        return 0;
    }

    else if(x == 210 && y == 30) {
        return 1;
    }

    else if(x == 390 && y == 30) {
        return 2;
    }

    else if(x == 30 && y == 210) {
        return 3;
    }

    else if(x == 210 && y == 210) {
        return 4;
    }

    else if(x == 390 && y == 210) {
        return 5;
    }

    else if(x == 30 && y == 390) {
        return 6;
    }

    else if(x == 210 && y == 390) {
        return 7;
    }

    else if(x == 390 && y == 390) {
        return 8;
    }

    else return 0;
}

int Plateau::vectorContains(int caseNumber, Player player) {
    for (size_t i = 0; i < pieceList.size(); ++i) {
        if(pieceList[i]->caseNumber == caseNumber && pieceList[i]->player == player) {
            return true;
        }
    }

    return false;
}

Player Plateau::lineDone() {
    // 0 - 1 - 2
    // 3 - 4 - 5
    // 6 - 7 - 8

    //if pieces >= 3
    if(pieceList.size() >= 3) {
        // horirontals
        // 0 && 1 && 2
        if(vectorContains(0, circle) && vectorContains(1, circle) && vectorContains(2, circle)) return circle;
        if(vectorContains(0, cross) && vectorContains(1, cross) && vectorContains(2, cross)) return cross;
        // 3 && 4 && 5
        if(vectorContains(3, circle) && vectorContains(4, circle) && vectorContains(5, circle)) return circle;
        if(vectorContains(3, cross) && vectorContains(4, cross) && vectorContains(5, cross)) return cross;
        // 6 && 7 && 8
        if(vectorContains(6, circle) && vectorContains(7, circle) && vectorContains(8, circle)) return circle;
        if(vectorContains(6, cross) && vectorContains(7, cross) && vectorContains(8, cross)) return cross;

        // verticals
        // 0 && 3 && 6
        if(vectorContains(0, circle) && vectorContains(3, circle) && vectorContains(6, circle)) return circle;
        if(vectorContains(0, cross) && vectorContains(3, cross) && vectorContains(6, cross)) return cross;
        // 1 && 4 && 7
        if(vectorContains(1, circle) && vectorContains(4, circle) && vectorContains(7, circle)) return circle;
        if(vectorContains(1, cross) && vectorContains(4, cross) && vectorContains(7, cross)) return cross;
        // 2 && 5 && 8
        if(vectorContains(2, circle) && vectorContains(5, circle) && vectorContains(8, circle)) return circle;
        if(vectorContains(2, cross) && vectorContains(5, cross) && vectorContains(8, cross)) return cross;

        // diagonals
        // 0 && 4 && 8
        if(vectorContains(0, circle) && vectorContains(4, circle) && vectorContains(8, circle)) return circle;
        if(vectorContains(0, cross) && vectorContains(4, cross) && vectorContains(8, cross)) return cross;
        // 2 && 4 && 6
        if(vectorContains(2, circle) && vectorContains(4, circle) && vectorContains(6, circle)) return circle;
        if(vectorContains(2, cross) && vectorContains(4, cross) && vectorContains(6, cross)) return cross;
    }

    return none;
}
