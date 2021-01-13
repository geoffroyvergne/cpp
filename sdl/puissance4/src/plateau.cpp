#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include <plateau.hpp>

Plateau::Plateau(SDL_Renderer *render, SDL_Texture *sdl_texture) {
    this->render = render;
    //sdl_texture = IMG_LoadTexture(render, imagePath.c_str());
    this->sdl_texture = sdl_texture;

    srcTextureParams = { 70, 139,  512, 460 };
    destTextureParams = { 11, 85,  512, 460 };
}

Plateau::~Plateau() {
    cleanup();
}

void Plateau::displayPieces() {
    for (size_t i = 0; i < this->pieceList.size(); ++i) {
        this->pieceList[i]->display();
	}
}

int Plateau::addNewPiece(Piece *currentPiece) {    
    Piece *piece = new Piece(render, currentPiece->type, sdl_texture);
    piece->destTextureParams.x = currentPiece->destTextureParams.x;
    piece->destTextureParams.y = 429;

    getCaseNumberByTextureParams(piece);

    //first row : 69
    //lastRow : 430
    //SDL_Log("Case Number %d", piece->caseNumber);
    //SDL_Log("piece->destTextureParams.y %d", piece->destTextureParams.y);

    int rowFull = false;
    
    while(caseAlreadyUsed(piece)) {
        rowFull = piece->moveUp();
        if(rowFull) break;
    }

    if(! rowFull) {
        pieceList.push_back(piece);        
    } 

    return rowFull;
}

int Plateau::caseAlreadyUsed(Piece *piece) {
     for (size_t i = 0; i < this->pieceList.size(); ++i) {
         if(piece->destTextureParams.x == this->pieceList[i]->destTextureParams.x && piece->destTextureParams.y == this->pieceList[i]->destTextureParams.y) {
             return true;
         }
     }

     return false;
}

void Plateau::getCaseNumberByTextureParams(Piece *piece) {
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

    int rowArray[] = { 69, 141, 213, 285, 357, 429 };
    int lineArray[] = { 26, 93, 160, 227, 294, 361, 428 };

    for(int row=0; row<6; row++) {
        for(int line=0; line<7; line++) {
            //SDL_Log("lineArray[line] %d rowArray[row] %d ", lineArray[line], rowArray[row]);
            
            if(piece->destTextureParams.x == lineArray[line] && piece->destTextureParams.y == rowArray[row]) {
                piece->position = { caseNumber, rowArray[row], lineArray[line] };
                piece->caseNumber = caseNumber;

                break;                
            }
            caseNumber++;
        }
    }

    //SDL_Log("destTextureParams.x %d destTextureParams.y %d", piece->destTextureParams.x, piece->destTextureParams.y);
    //SDL_Log("Case Number %d", piece->caseNumber);
}

//TODO implement
Player Plateau::lineDone() {
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

    return winner;
}

void Plateau::display() {
    //SDL_RenderCopy(render, sdl_texture, NULL, &textureParams);
    SDL_RenderCopy(render, sdl_texture, &srcTextureParams, &destTextureParams);
}

void Plateau::cleanup() {
    //SDL_DestroyTexture(sdl_texture);
}

