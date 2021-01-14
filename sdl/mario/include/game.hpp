#include <iostream>
#include <SDL.h>
#include <message.hpp>

#ifndef GAME
#define GAME

class Game {
    public:
        //Game();
        ~Game();
        std::string name = "Mario";
        int width = 500;
        int height = 500;
        int loopDelay = 10;

        SDL_Window *window;
        SDL_Renderer *render;
        Message *intro;

        void init();
        void renderView();
        void startLoop();
        void displayIntro();
        void displayGame();
        
        void cleanup();
};

#endif
