#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <player.hpp>
#include <piece_type.hpp>

#ifndef CIRCLE
#define CIRCLE

struct Position {
    int caseNumber = 0;
    int x;
    int y;
};

struct Texture {
    int x;
    int y;
};

class Piece {
    public:
        Piece(PieceType type);
        ~Piece();
        Player player;       
        SDL_Rect srcTextureParams;
        SDL_Rect destTextureParams = { 250, 250,  50, 50 };
        Position position;
        Texture texture;
        PieceType pieceType;

        /*int x;
        int y;*/
        SDL_Color color;
        int size = 50;
        int thick = 10;

        void togglePlayer(PieceType pieceType);
        void display();
        void moveUp();
        void moveDown();
        void moveRight();
        void moveLeft();
        void cleanup();

        void caseNumberByTextureParams();

        void displayCross(SDL_Color color);
        void displayCircle(SDL_Color color);
};

#endif
