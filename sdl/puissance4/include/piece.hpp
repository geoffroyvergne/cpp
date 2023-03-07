#include <iostream>
#include <SDL.h>

#include <player.hpp>

#ifndef PIECE
#define PIECE

struct Position {
    int caseNumber;
    int x;
    int y;
};

struct Texture {
    int x;
    int y;
};

enum class PieceType {
    none,
    yellow,
    red
};

class Piece {    
    public:
        Piece(PieceType pieceType);
        ~Piece();
        PieceType type = PieceType::none;
        Player player = Player::none;

        Position position;
        Texture texture;

        SDL_Color color;

        bool rowFull = false;

        void togglePlayer(PieceType pieceype);
        bool moveUp();
        void moveDown();
        void moveRight();
        void moveLeft();
        void display();
        void cleanup();
};

#endif
