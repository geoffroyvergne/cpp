#include <iostream>
#include <SDL.h>
#include <board.hpp>
#include <square.hpp>
#include <piece.hpp>
#include <color.hpp>
#include <array>
#include <vector>
#include <sdl-core.hpp>

Board::Board() { 
    init();
    addPieces();
}

Board::~Board() { 
    cleanup();
}

void Board::init() {    
    int squareId = 0;
    Color color = black;

    for (int i = 0; i < 8; ++i) {
        std::vector<Square> v1;
        
        for (int j = 0; j < 8; ++j) {            

            if(j >0) color = toggleColor(color);
            
            Square *square = new Square(color, squareId);
            square->x = j;
            square->y = i;

            if(i == 3 && j == 3) square->selected = true;
            //square->destTextureParams.x += i *SdlCore::getInstance()->width; 
            //square->destTextureParams.y += j *SdlCore::getInstance()->width; 
            v1.push_back(*square);

            squareId++;
        }
        squareList.push_back(v1);
    }
}

Color Board::toggleColor(Color color) {
    if(color == white) return black;
    else if(color == black) return white;
    else return color;
}

void Board::addPieces() {
    std::vector<std::vector<int>> plateauPiecesDef;
    
    /*if(empty) {
        plateauPiecesDef = {
            {
                { 0, 0, 0, 0, 0, 0, 0, 0 },
                { 0, 0, 0, 0, 0, 0, 0, 0 },
                { 0, 0, 0, 0, 0, 0, 0, 0 },
                { 0, 0, 0, 0, 0, 0, 0, 0 },
                { 0, 0, 0, 0, 0, 0, 0, 0 },
                { 0, 0, 0, 0, 0, 0, 0, 0 },
                { 0, 0, 0, 0, 0, 0, 0, 0 },
                { 0, 0, 0, 0, 0, 0, 0, 0 },
            }
        };*/
   
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
    
    pieceList.clear();

    int pieceId = 0;
    Color pieceColor = transparent;
    for (int i = 0; i < plateauPiecesDef.size(); ++i) {
        std::vector<Piece> v1;
        for (int j = 0; j < plateauPiecesDef[i].size(); ++j) {

            /*if(plateauPiecesDef[i][j] == 0) {                
                continue;
            }*/

            if(i <= 2) pieceColor = black;
            else if(i >= 6) pieceColor = white;
            else pieceColor = transparent;
            
            Piece *piece = new Piece(static_cast<PieceType>(plateauPiecesDef[i][j]), pieceColor);
            
            piece->id = pieceId;
            piece->destTextureParams.x += (j-1) *SdlCore::getInstance()->size; 
            piece->destTextureParams.y += (i-1) *SdlCore::getInstance()->size; 
            //squareList.at(pieceId)->piece = piece;

            piece->x = j;
            piece->y = i;

            v1.push_back(*piece);

            pieceId++;
        }
        pieceList.push_back(v1);
    }
}

Piece* Board::getNonePiece() {
    return new Piece(none, transparent);
}

void Board::reset() {    
    init();
    addPieces();
}

void Board::deletePiece(Piece* piece) {
   if(pieceList[piece->y][piece->x].type != none) {
        pieceList[piece->y][piece->x] = *getNonePiece();
   }
}

bool Board::caseAlreadyUsed(Piece* piece) {
    if(pieceList[piece->y][piece->x].type == none) return false;
    return true;
}

void Board::displayBoard() {
    for (size_t i = 0; i < squareList.size(); ++i) {
        for (size_t j = 0; j < squareList[i].size(); ++j) {
            this->squareList[i][j].display();
        }
    }
}
 
void Board::display() {
    for (size_t i = 0; i < pieceList.size(); ++i) {
        for (size_t j = 0; j < pieceList[i].size(); ++j) {
            if(this->pieceList[i][j].type != none) this->pieceList[i][j].display();
        }
    }
}

void Board::logBoard() {
    for (size_t i = 0; i < pieceList.size(); ++i) {        
        for (size_t j = 0; j < pieceList[i].size(); ++j) {
            std::cout << this->pieceList[i][j].type << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Board::cleanup() {
    
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