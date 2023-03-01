#include <iostream>
#include <SDL.h>

#include <piece_type.hpp>
#include <player.hpp>

#ifndef PIECE
#define PIECE

struct Position {
    int caseNumber;
    int x;
    int y;
};

class Piece {
    //private:
    //    Player player;
    public:
        Piece(PieceType type);
        ~Piece();
        PieceType type;
        Player player = Player::player_none;

        SDL_Rect srcTextureParams;
        SDL_Rect destTextureParams;

        Position position;

        void togglePlayer(PieceType pieceype);
        bool moveUp();
        void moveDown();
        void moveRight();
        void moveLeft();
        void display();
        void cleanup();
        //Player getPlayer();
        int getPlayer(Player player);
};

#endif
