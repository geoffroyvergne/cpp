#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <tile.hpp>
#include <world.hpp>
#include <player.hpp>

#ifndef LEVEL
#define LEVEL

class Level {
    public:
        Level(World world, SDL_Renderer *render, SDL_Texture *sdl_texture_levels, SDL_Texture *sdl_texture_enemies);
        ~Level();
        World world;
        SDL_Renderer *render;
        SDL_Texture *sdl_texture_levels;
        SDL_Texture *sdl_texture_enemies;
        std::vector<Tile*> tileList;
        int tileSize = 30;

        void setIntro();
        bool detectCollision(Player *player);
        bool detectCollisionFall(Player *player);
        void moveRight();
        void moveLeft();
        void setLevel(World world);
        void setLevel00();
        void setLevel11();
        std::string getLevelName();
        void setLevel();
        void display();
        void cleanUp();
};

#endif
