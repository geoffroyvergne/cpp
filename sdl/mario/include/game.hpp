#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <message.hpp>
#include <level.hpp>
#include <world.hpp>

#ifndef GAME
#define GAME

class Game {
    public:
        Game();
        ~Game();
        std::string name = "Mario";
        int width = 500;
        int height = 400;
        int loopDelay = 10;

        SDL_Window *window;
        SDL_Renderer *render;
        SDL_Texture *sdl_texture_levels;
        SDL_Texture *sdl_texture_enemies;
        Message *intro;
        Level *currentLevel;

        void init();
        void renderView();
        void startLoop();
        void displayIntro();
        void displayGame();
        void newLevel(World world);
        
        void cleanup();
};

#endif
