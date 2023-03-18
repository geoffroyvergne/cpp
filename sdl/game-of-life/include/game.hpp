#include <iostream>
#include <SDL.h>
#include <sdl-core.hpp>
#include <plateau.hpp>

#ifndef GAME
#define GAME

class Game {
    public:
        //Game();
        ~Game();

        /*int width = 1000;
        int height = 1000;
        int loopDelay = 1000;*/

        //int period = 10;
        bool pause = true;

        Plateau *plateau;

        void renderView();
        void startLoop();

        void newGame();        

};

#endif
