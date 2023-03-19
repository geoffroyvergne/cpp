#include <iostream>
#include <SDL.h>
#include <sdl-core.hpp>
#include <board.hpp>

#ifndef GAME
#define GAME

class Game {
    public:
        //Game();
        ~Game();

        bool pause = true;

        Board *board;

        void renderView();
        void startLoop();

        void newGame();        

};

#endif
