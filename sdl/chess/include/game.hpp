#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include <board.hpp>
#include <cursor.hpp>
#include <color.hpp>

#ifndef GAME
#define GAME

struct Player {
    int id;
    std::string name;
    int score = 0;
    bool winner = false;
    Color color;
};

class Game {
    public:
        Game();
        ~Game();

        Board* board;
        Cursor* cursor;
        Player player1;
        Player player2;
        Player currentPlayer;
       
        void reset();

        void cursorUp();
        void cursorDown();
        void cursorLeft();
        void cursorRight();

        void deletePiece();
        void selectPiece();
        void validatePiece();
        void cancelSelectPiece();
        void togglePlayer();

        void renderView();
        void startLoop();        
};

#endif
