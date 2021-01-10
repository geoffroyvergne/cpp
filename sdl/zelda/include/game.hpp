#include <iostream>
#include <SDL.h>

//#include <map>
//#include <iterator>

#include <player.hpp>
//#include <player-action.hpp>
#include <level.hpp>
#include <sprite-type.hpp>

#ifndef GAME
#define GAME

class Game {
    public:
        //Game();
        ~Game();
        std::string name = "Zelda";
        int width = 512;
        int height = 480;
        int loopDelay = 10;

        SDL_Window *window;
        SDL_Renderer *render;
        Player *player;
        //std::map<int, *Level> levels;
        Level *currentLevel;
        
        void init();
        void renderView();
        void startLoop();
        //Sprite *addSprite(int x, int y, SpriteType type)
        Sprite *getSprite(SpriteType type, int x, int y);
        void addSpritesLevel();
        void cleanup();
};

#endif