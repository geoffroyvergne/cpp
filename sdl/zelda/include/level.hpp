#include <iostream>
#include <SDL.h>
#include <vector>
#include <sprite.hpp>
#include <player.hpp>
#include <levels.hpp>
#include <enemy.hpp>
#include <sprite-type.hpp>

#ifndef LEVEL
#define LEVEL

class Level {
    public:
        Level(SDL_Renderer *render, Levels number,  SDL_Texture *sdl_texture_overworld, SDL_Texture *sdl_texture_overworld_enemies);
        ~Level();
        std::string imagePath;
        std::vector<Sprite*> spriteList;
        std::vector<Enemy*> enemyList;
        Levels number;
        std::string name = "none";
        int spriteSize = 50;

        SDL_Renderer *render;
        SDL_Texture *sdl_texture_overworld;
        SDL_Texture *sdl_texture_overworld_enemies;
        SDL_Rect srcTextureParams; // Real texture size and placement
        SDL_Rect destTextureParams; // Texture seen in game

        Levels currentNumber = none;
        Levels leftNumber = none;
        Levels rightNumber = none;
        Levels upNumber = none;
        Levels downNumber = none;

        void move(Levels levels);
        bool detectCollision(Player *player);
        Enemy *getEnemy(EnemyType type, int x, int y);
        Sprite *getSprite(SpriteType type, int x, int y);
        void addEnemies(Levels number);
        void addSprites(Levels number);
        void pushLevel(std::array<std::array<int, 12>, 10> *levelDef);
        void display();
        void cleanup();
};

#endif
