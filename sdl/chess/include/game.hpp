#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include <plateau.hpp>
#include <cursor.hpp>

#ifndef GAME
#define GAME

class Game {
    public:
        Game();
        ~Game();

        Plateau* plateau;
        Cursor* cursor;
       
        void reset();

        void cursorUp();
        void cursorDown();
        void cursorLeft();
        void cursorRight();

        void deletePiece();
        void selectPiece();
        void validatePiece();
        void cancelSelectPiece();

        void renderView();
        void startLoop();        
};

#endif
