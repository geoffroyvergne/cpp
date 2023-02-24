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
        Level(Worlds number);
        ~Level();
        std::vector<Sprite*> spriteList;
        std::vector<Enemy*> enemyList;
        Worlds number;
        std::string name = "none";
        int spriteSize = 50;
        
        Worlds currentNumber = none;
        Worlds leftNumber = none;
        Worlds rightNumber = none;
        Worlds upNumber = none;
        Worlds downNumber = none;

        Worlds bellowNumber = none;
        Worlds upponNumber = none;

        void move(Worlds levels);
        bool detectCollision(Player *player);
        Enemy *getEnemy(EnemyType type, int x, int y);
        Sprite *getSprite(SpriteType type, int x, int y);
        void addEnemies(Worlds number);
        void addSprites(Worlds number);
        void pushLevel(std::array<std::array<int, 12>, 10> *levelDef);
        void display();
        void cleanup();
};

#endif
