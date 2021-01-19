#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <message.hpp>
#include <level.hpp>
#include <world.hpp>
#include <player.hpp>

#ifndef GAME
#define GAME

class Game {
    public:
        Game();
        ~Game();
        std::string name = "Mario";
        int height = 500;
        int width = 600;
        int loopDelay = 100;

        SDL_Window *window;
        SDL_Renderer *render;
        SDL_Texture *sdl_texture_levels;
        SDL_Texture *sdl_texture_enemies;
        Message *intro;
        Level *currentLevel;
        Player *player;

        void init();
        void renderView();
        void startLoop();
        void displayIntro();
        void displayGame();
        void newLevel(World world);
        
        void moveLeft(const Uint8 *state);
        void moveRight(const Uint8 *state);
        void moveDown(const Uint8 *state);
        void moveUp(const Uint8 *state);

        void jump(const Uint8 *state);
        void walkLeft(const Uint8 *state);
        void walkRight(const Uint8 *state);
        void fall(const Uint8 *state);
        
        void cleanup();
};

#endif
