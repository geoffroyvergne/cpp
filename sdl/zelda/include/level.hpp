#include <iostream>
#include <SDL.h>
#include <vector>
#include <sprite.hpp>
#include <player.hpp>
#include <levels.hpp>

#ifndef LEVEL
#define LEVEL

class Level {
    public:
        Level(SDL_Renderer *render, Levels number, SDL_Texture *sdl_texture);
        ~Level();
        std::string imagePath;
        std::vector<Sprite*> spriteList;
        Levels number;

        SDL_Renderer *render;
        SDL_Texture *sdl_texture;
        SDL_Rect srcTextureParams; // Real texture size and placement
        SDL_Rect destTextureParams; // Texture seen in game

        Level *left;
        Level *right;
        Level *up;
        Level *down;

        bool detectCollision(Player *player);
        void display();
        void cleanup();
};

#endif
