#include <iostream>
#include <SDL.h>

//#include <map>
//#include <iterator>

#include <player.hpp>
//#include <player-action.hpp>
#include <level.hpp>
#include <sprite-type.hpp>
#include <levels.hpp>

#ifndef GAME
#define GAME

class Game {
    public:
        //Game();
        ~Game();
        std::string name = "Zelda";
        int width = 500;
        int height = 500;
        int loopDelay = 10;

        SDL_Window *window;
        SDL_Renderer *render;
        //SDL_Texture *sdl_texture;
        SDL_Texture *sdl_texture_items;
        Player *player;
        Level *currentLevel;
        
        void init();
        void addLevel(Levels level);
        void displayDashboard();
        void renderView();
        void startLoop();
        
        void cleanup();
};

#endif