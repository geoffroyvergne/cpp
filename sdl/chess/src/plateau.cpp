#include <iostream>
#include <SDL.h>
#include <plateau.hpp>
#include <square.hpp>
#include <piece.hpp>
#include <color.hpp>
#include <array>
#include <core.hpp>

Plateau::Plateau(int squareWidth, int border) { 
    this->squareWidth = squareWidth;    
    this->border = border;

    init();
}

Plateau::~Plateau() { 
    cleanup();
}

/*
    1   2   3   4   5   6   7   8
    a   b   c   d   e   f   g   h
8   0   1   2   3   4   5   6   7   8
7   8   9   10  11  12  13  14  15  7
6   16  17  18  19  20  21  22  23  6
5   24  25  26  27  28  29  30  31  5
4   32  33  34  35  36  37  38  39  4
3   40  41  42  43  44  45  46  47  3
2   48  49  50  51  52  53  54  55  2
1   56  57  58  59  60  61  62  63  1
    a   b   c   d   e   f   g   h
    1   2   3   4   5   6   7   8
*/

/*

    a   b   c   d   e   f   g   h
8   R   k   b   Q   K   b   k   R   8
7   p   p   p   p   p   p   p   p   7
6   n   n   n   n   n   n   n   n   6
5   n   n   n   n   n   n   n   n   5
4   n   n   n   n   n   n   n   n   4
3   n   n   n   n   n   n   n   n   3
2   p   p   p   p   p   p   p   p   2
1   R   k   b   Q   K   b   k   R   1
    a   b   c   d   e   f   g   h

*/

/*

    a   b   c   d   e   f   g   h
8   a8  b8  c8  d8  e8  f8  g8  h8  8
7   a7  b7  c7  d7  e7  f7  g7  h7  7
6   a6  b6  c6  d6  e6  f6  g6  h6  6
5   a5  b5  c5  d5  e5  f5  g5  h5  5
4   a4  b4  c4  d4  e4  f4  g4  h4  4
3   a3  b3  c3  d3  e3  f3  g3  h3  3
2   a2  b2  c2  d2  e2  f2  g2  h2  2
1   a1  b1  c1  d1  e1  f1  g1  h1  1
    a   b   c   d   e   f   g   h

*/

void Plateau::init() {
    std::array<std::array<int, 8>, 8>
    plateauDef = {
                    {
                        { 2, 1, 2, 1, 2, 1, 2, 1 },
                        { 1, 2, 1, 2, 1, 2, 1, 2 },
                        { 2, 1, 2, 1, 2, 1, 2, 1 },
                        { 1, 2, 1, 2, 1, 2, 1, 2 },
                        { 2, 1, 2, 1, 2, 1, 2, 1 },
                        { 1, 2, 1, 2, 1, 2, 1, 2 },
                        { 2, 1, 2, 1, 2, 1, 2, 1 },
                        { 1, 2, 1, 2, 1, 2, 1, 2 },
                    }
                };

    int squareId = 0;
    for (int i = 0; i < plateauDef.size(); ++i) {        
        for (int j = 0; j < plateauDef[i].size(); ++j) {
            //if(static_cast<SquareType>(plateauDef[i][j]) == empty) continue;
            
            Square *square = new Square(static_cast<Color>(plateauDef[i][j]), squareWidth, squareId);
            if(i == 3 && j == 3) square->selected = true;
            square->destTextureParams.x += i *squareWidth; 
            square->destTextureParams.y += j *squareWidth; 
            squareList.push_back(square);

            squareId++;
        }
    }

    std::array<std::array<int, 8>, 8> 
    plateauPiecesDef = {
                    {
                        { 3, 5, 4, 1, 2, 4, 5, 3 },
                        { 6, 6, 6, 6, 6, 6, 6, 6 },
                        { 0, 0, 0, 0, 0, 0, 0, 0 },
                        { 0, 0, 0, 0, 0, 0, 0, 0 },
                        { 0, 0, 0, 0, 0, 0, 0, 0 },
                        { 0, 0, 0, 0, 0, 0, 0, 0 },
                        { 6, 6, 6, 6, 6, 6, 6, 6 },
                        { 3, 5, 4, 1, 2, 4, 5, 3 },
                    }
                };

    int pieceId = 0;
    Color pieceColor = transparent;
    for (int i = 0; i < plateauPiecesDef.size(); ++i) {
        for (int j = 0; j < plateauPiecesDef[i].size(); ++j) {
            if(static_cast<PieceType>(plateauPiecesDef[i][j]) == none) {
                pieceId++;
                continue;
            }
            
            if(i <= 2) pieceColor = black;
            else if(i >= 6) pieceColor = white;
            else pieceColor = transparent;
            
            Piece *piece = new Piece(static_cast<PieceType>(plateauPiecesDef[i][j]), pieceColor, squareWidth, border);
            
            piece->id = pieceId;
            piece->destTextureParams.x += j *squareWidth; 
            piece->destTextureParams.y += i *squareWidth; 
            //squareList.at(pieceId)->piece = piece;

            pieceList.push_back(piece);

            pieceId++;
        }
    }
}

void Plateau::reset() {
    //TODO fixe it
    for(int i=0; i<5; i++) {
        for (size_t i = 0; i < this->pieceList.size(); ++i) {
            //this->pieceList[i]->cleanup();
            this->pieceList.erase(this->pieceList.begin() + i);   
        }
    }
    init();
}

void Plateau::deletePieceById(int id) {
    for (size_t i = 0; i < this->pieceList.size(); ++i) {
        if(this->pieceList[i]->id == id) {
            this->pieceList.erase(this->pieceList.begin() + i);
        }
    }
}

Piece* Plateau::getPieceById(int id) {
    for (size_t i = 0; i < pieceList.size(); ++i) {
        if(id == this->pieceList[i]->id) {
            return this->pieceList[i];
        }
    }

    return NULL;
}

Square* Plateau::getSquareById(int id) {
    for (size_t i = 0; i < squareList.size(); ++i) {
        if(id == this->squareList[i]->id) {
            return this->squareList[i];
        }
    }

    return NULL;
}

bool Plateau::caseAlreadyUsed(int id) {
    if(this->getPieceById(id) != NULL) return true;

    return false;
}

std::string Plateau::getSquarePositionById(int id) {
    switch(id) {
        case 0:  return "a8"; case 1:  return "b8"; case 2:  return "c8"; case 3:  return "d8"; case 4:  return "e8"; case 5:  return "f8"; case 6:  return "g8"; case 7:  return "h8"; 
        case 8:  return "a7"; case 9:  return "b7"; case 10: return "c7"; case 11: return "d7"; case 12: return "e7"; case 13: return "f7"; case 14: return "g7"; case 15: return "h7";
        case 16: return "a6"; case 17: return "b6"; case 18: return "c6"; case 19: return "d6"; case 20: return "e6"; case 21: return "f6"; case 22: return "g6"; case 23: return "h6"; 
        case 24: return "a5"; case 25: return "b5"; case 26: return "c5"; case 27: return "d5"; case 28: return "e5"; case 29: return "f5"; case 30: return "g5"; case 31: return "h5"; 
        case 32: return "a4"; case 33: return "b4"; case 34: return "c4"; case 35: return "d4"; case 36: return "e4"; case 37: return "f4"; case 38: return "g4"; case 39: return "h4"; 
        case 40: return "a3"; case 41: return "b3"; case 42: return "c3"; case 43: return "d3"; case 44: return "e3"; case 45: return "f3"; case 46: return "g3"; case 47: return "h3"; 
        case 48: return "a2"; case 49: return "b2"; case 50: return "c2"; case 51: return "d2"; case 52: return "e2"; case 53: return "f2"; case 54: return "g2"; case 55: return "h2"; 
        case 56: return "a1"; case 57: return "b1"; case 58: return "c1"; case 59: return "d1"; case 60: return "e1"; case 61: return "f1"; case 62: return "g1"; case 63: return "h1"; 
    }

    return "none";
}
 
void Plateau::display() {
    for (size_t i = 0; i < squareList.size(); ++i) {
        this->squareList[i]->display();
    }

    for (size_t i = 0; i < pieceList.size(); ++i) {
        this->pieceList[i]->display();
    }
}

void Plateau::cleanup() {
    /*for (size_t i = 0; i < squareList.size(); ++i) {
        SDL_DestroyTexture(this->squareList[i]->sdl_texture);
    }

    for (size_t i = 0; i < squareList.size(); ++i) {
        if(this->squareList[i]->piece != NULL) {
            //SDL_DestroyTexture(this->squareList[i]->piece->sdl_texture);
        }
    }*/
}
