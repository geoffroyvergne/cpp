#include <iostream>
#include <SDL.h>
#include <plateau.hpp>
#include <square.hpp>
#include <piece.hpp>
#include <color.hpp>
#include <array>

Plateau::Plateau(SDL_Renderer *render, SDL_Texture *sdl_texture, int squareWidth) { 
    this->squareWidth = squareWidth;
    this->render = render;
    this->sdl_texture = sdl_texture;

    init();
}

Plateau::~Plateau() { 
    cleanup();
}

/*

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

/*void Plateau::init() {
    
    Square *a8 = new Square(render, sdl_texture, white, squareWidth, 0);
    Square *b8 = new Square(render, sdl_texture, black, squareWidth, 1);
    Square *c8 = new Square(render, sdl_texture, white, squareWidth, 2);

    Square *a7 = new Square(render, sdl_texture, black, squareWidth, 8);
    Square *b7 = new Square(render, sdl_texture, white, squareWidth, 9);
    Square *c7 = new Square(render, sdl_texture, black, squareWidth, 10);

    Square *a6 = new Square(render, sdl_texture, white, squareWidth, 16);
    Square *b6 = new Square(render, sdl_texture, black, squareWidth, 17);
    Square *c6 = new Square(render, sdl_texture, white, squareWidth, 18);

    b7->up = b8;
    b7->down = b6;
    b7->left = a7;
    b7->right = c7;
}*/

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
            
            Square *square = new Square(render, sdl_texture, static_cast<Color>(plateauDef[i][j]), squareWidth, squareId);
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
            
            squareList.at(pieceId)->piece = new Piece(render, sdl_texture, static_cast<PieceType>(plateauPiecesDef[i][j]), pieceColor, squareWidth);
            
            squareList.at(pieceId)->piece->id = pieceId;
            squareList.at(pieceId)->piece->destTextureParams.x += j *squareWidth; 
            squareList.at(pieceId)->piece->destTextureParams.y += i *squareWidth; 
            //pieceList.push_back(piece);

            //squareList.at(pieceId)->piece = piece;

            pieceId++;
        }
    }
}

Piece* Plateau::getPieceById(int id) {
    Square *square = getSquareById(id);
    if(square->piece != NULL) {
        return square->piece;
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

void Plateau::display() {
    for (size_t i = 0; i < squareList.size(); ++i) {
        this->squareList[i]->display();
    }

    for (size_t i = 0; i < squareList.size(); ++i) {
        if(this->squareList[i]->piece != nullptr) {
            this->squareList[i]->piece->display();
        }
    }
}

void Plateau::cleanup() {
    for (size_t i = 0; i < squareList.size(); ++i) {
        SDL_DestroyTexture(this->squareList[i]->sdl_texture);
    }

    for (size_t i = 0; i < squareList.size(); ++i) {
        if(this->squareList[i]->piece != NULL) {
            //SDL_DestroyTexture(this->squareList[i]->piece->sdl_texture);
        }
    }
}
