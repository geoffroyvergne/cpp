#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <array>

#include <level.hpp>
#include <levels.hpp>
#include <core.hpp>

Level::Level(Levels number) {    
    this->number = number;
    this->move(number);

    addSprites(number);
    addEnemies(number);
}

Level::~Level() { 
    cleanup();
}

/*

a   a01 a02 a03 a04 a05 a06 a07 a08 a09 a10 a11 a12 a13 a14 a15 a16
b   b01 b02 b03 b04 b05 b06 b07 b08 b09 b10 b11 b12 b13 b14 b15 b16
c   c01 c02 c03 c04 c05 c06 c07 c08 c09 c10 c11 c12 c13 c14 c15 c16
d   d01 d02 d03 d04 d05 d06 d07 d08 d09 d10 d11 d12 d13 d14 d15 d16
e   e01 e02 e03 e04 e05 e06 e07 e08 e09 e10 e11 e12 e13 e14 e15 e16
f   f01 f02 f03 f04 f05 f06 f07 f08 f09 f10 f11 f12 f13 f14 f15 f16
g   g01 g02 g03 g04 g05 g06 g07 g08 g09 g10 g11 g12 g13 g14 g15 g16
h   h01 h02 h03 h04 h05 h06 h07 h08 h09 h10 h11 h12 h13 h14 h15 h16
    01  02  03  04  05  06  07  08  09  10  11  12  13  14  15  16

*/

//first level : h08 right h09 left h07 up g08 down NULL

void Level::move(Levels levels) {
    switch(levels) {
        case h07 : 
            name = "h07";
            rightNumber = h08;
            break;

        case h08 : 
            name = "h08";
            leftNumber = h07;
            rightNumber = h09;
            upNumber = g08;
            break;

        case h09 : 
            name = "h09";
            leftNumber = h08;
            rightNumber = h10;
            upNumber = g09;
            break;

        case h10 : 
            name = "h10";
            leftNumber = h09;           
            break;

        case g08 : 
            name = "g08";
            downNumber = h08;
            rightNumber = g09;
            break;

        case g09 : 
            name = "g08";
            leftNumber = g08;
            downNumber = h09;
            break;

        default:
            break;
    }
}

bool Level::detectCollision(Player *player) {
    SDL_bool collision;

    for (size_t i = 0; i < spriteList.size(); ++i) {
        if(this->spriteList[i]->collide) {
            collision = SDL_HasIntersection(&this->spriteList[i]->destTextureParams, &player->destTextureParams);
            if(collision) return true;
        }
    }

    for (size_t i = 0; i < enemyList.size(); ++i) {
        if(this->enemyList[i]->collide) {
            collision = SDL_HasIntersection(&this->enemyList[i]->destTextureParams, &player->destTextureParams);
            
            if(collision) {
                // collision with enemy means one life less if not in attack mode
                if(player->isAttack()) {
                    this->enemyList.erase(this->enemyList.begin() + i);
                    //this->enemyList[i]->cleanup();
                    //std::cout << "kill enemy" << std::endl;
                    SDL_Log("kill enemy");
                } else {
                    player->lives --;
                }
            
                return true;
            }
        }
    }

    return false;
}

Enemy* Level::getEnemy(EnemyType type, int x, int y) {
    switch(type) {
        case red_octorok : 
            {
                Enemy *enemy = new Enemy();
                enemy->srcTextureParams = { 1, 11,  15, 16 };
                enemy->destTextureParams = { x, y,  50, 50 };
                //sprite->collide = false;

                return enemy;
            }
        break;
    }
}

Sprite* Level::getSprite(SpriteType type, int x, int y) {
    switch(type) {
        case door : 
            {
                Sprite *sprite = new Sprite();
                sprite->srcTextureParams = { 362, 164,  4, 4 };
                sprite->destTextureParams = { x, y,  spriteSize, spriteSize };
                sprite->collide = false;

                return sprite;
            }
        break; 
        case green_rock_standalone : 
            {
                Sprite *sprite = new Sprite();
                sprite->srcTextureParams = { 290, 107,  15, 16 };
                sprite->destTextureParams = { x, y,  spriteSize, spriteSize };

                return sprite;
            }
        break;
        case green_rock : 
            {
                Sprite *sprite = new Sprite();
                sprite->srcTextureParams = { 355, 107,  15, 16 };
                sprite->destTextureParams = { x, y,  spriteSize, spriteSize };

                return sprite;
            }
        break; 
        case green_rock_corner_low_right : 
            {
                Sprite *sprite = new Sprite();
                sprite->srcTextureParams = { 371, 107,  15, 16 };
                sprite->destTextureParams = { x, y,  spriteSize, spriteSize };
                sprite->collide = false;

                return sprite;
            }
        break;
        case green_bush : 
            {
                Sprite *sprite = new Sprite();
                sprite->srcTextureParams = { 314, 107,  15, 16 };
                sprite->destTextureParams = { x, y,  spriteSize, spriteSize };

                return sprite;
            }
        break;
        case green_tree : 
            {
                Sprite *sprite = new Sprite();
                sprite->srcTextureParams = { 275, 107,  15, 16 };
                sprite->destTextureParams = { x, y,  spriteSize, spriteSize };

                return sprite;
            }
        break;
        case brown_rock_standalone : 
            {
                Sprite *sprite = new Sprite();
                sprite->srcTextureParams = { 419, 107,  15, 16 };
                sprite->destTextureParams = { x, y,  spriteSize, spriteSize };

                return sprite;
            }
        break;
        case brown_rock : 
            {
                Sprite *sprite = new Sprite();
                sprite->srcTextureParams = { 478, 107,  15, 16 };
                sprite->destTextureParams = { x, y,  spriteSize, spriteSize };

                return sprite;
            }
        break; 

        default:
            return nullptr;
            break;
    };
}

void Level::addEnemies(Levels number) {
    int spriteSize = 50;

    switch(number) {
        case g08 :             
            enemyList.push_back(getEnemy(red_octorok, 50, 50));
            enemyList.push_back(getEnemy(red_octorok, 50, 300));
            enemyList.push_back(getEnemy(red_octorok, 300, 50));
            enemyList.push_back(getEnemy(red_octorok, 400, 300));

        default:
            break;
    };
}

void Level::addSprites(Levels number) {
    std::array<std::array<int, 12>, 10> levelDef;

    switch(number) {
        case h07 : 
            {                
                levelDef = {
                    {
                        {00, 00, 00, 00, 00, 00, 00, 00, 00, green_rock, 00, 00 },
                        {00, 00, 00, 00, 00, 00, 00, 00, 00, green_rock, 00, 00 },
                        {00, 00, 00, 00, 00, 00, 00, 00, 00, green_rock, 00, 00 },
                        {00, 00, 00, brown_rock_standalone, 00, 00, 00, 00, 00, green_rock, 00, 00 },
                        {00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00 },
                        {00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00 },
                        {00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00 },
                        {00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00 },
                        {00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00 },
                        {00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00 },
                    }
                };    

                /*for (int i = 0; i < levelDef.size(); ++i) {
                    for (int j = 0; j < levelDef[i].size(); ++j) {
                        if(static_cast<SpriteType>(levelDef[i][j]) == empty) continue;                        
                        spriteList.push_back(getSprite(static_cast<SpriteType>(levelDef[i][j]), j*spriteSize, i*spriteSize));
                    }
                }*/

                pushLevel(&levelDef);            
            }

            break;

        case h08 :             
            {
                levelDef = {
                    {
                        { green_rock, green_rock, green_rock, green_rock, green_rock, green_rock, green_rock, 00, 00, 00, 00, 00 },
                        { green_rock, green_rock, green_rock, green_rock, door, green_rock, green_rock_corner_low_right, 00, 00, 00, 00, 00 },
                        { green_rock, green_rock, green_rock, green_rock_corner_low_right, 00, 00, 00, 00, 00, 00, 00, 00 },
                        { green_rock, green_rock, green_rock_corner_low_right, 00, 00, 00, 00, 00, 00, 00, 00, 00 },
                        { green_rock, green_rock_corner_low_right, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00 },
                        { 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00 },
                        { 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00 },
                        { 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, },
                        { green_rock, green_bush, green_bush, green_bush, green_bush, green_bush, green_bush, green_bush, green_bush, green_bush, green_bush, green_bush },
                        { green_rock, green_rock, green_rock, green_rock, green_rock, green_rock, green_rock, green_rock, green_rock, green_rock, green_bush, green_bush },
                    }
                };    

                pushLevel(&levelDef); 
            }    

            break;

        case h09 :             
            {
                levelDef = {
                    {
                        { 00, 00, 00, 00, 00, 00, 00, 00, 00, green_tree, green_tree, green_tree },
                        { 00, 00, 00, 00, 00, 00, 00, 00, 00, green_tree, green_tree, green_tree },
                        { 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00 },
                        { 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00 },
                        { 00, 00, 00, 00, 00, green_tree, 00, 00, 00, 00, 00, 00 },
                        { 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00 },
                        { 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00 },
                        { 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00 },
                        { green_rock, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00 },
                        { green_rock, 00, 00, 00, 00, 00, 00, 00, 00, green_tree, green_tree, green_tree },
                    }
                };    

                pushLevel(&levelDef); 
            }    
            break;

        case h10 : 
            {
                levelDef = {
                    {
                        { brown_rock, brown_rock, brown_rock, brown_rock, brown_rock, brown_rock, brown_rock, brown_rock, brown_rock, brown_rock, brown_rock, brown_rock},
                        { 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00},
                        { 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00 },
                        { 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00 },
                        { 00, 00, 00, 00, 00, brown_rock_standalone, 00, 00, 00, 00, 00, 00 },
                        { 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00 },
                        { 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00 },
                        { 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00 },
                        { 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00 },
                        { brown_rock, brown_rock, brown_rock, brown_rock, brown_rock, brown_rock, brown_rock, brown_rock, brown_rock, brown_rock, brown_rock, brown_rock },
                    }
                };    

                pushLevel(&levelDef); 
            }    

            break;
        case g08 :             
            {
                levelDef = {
                    {
                        { 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00 },
                        { 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00 },
                        { 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00 },
                        { 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00 },
                        { 00, 00, 00, 00, green_rock_standalone, 00, 00, 00, 00, 00, 00, 00 },
                        { 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00 },
                        { 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00 },
                        { 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00 },
                        { 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00 },
                        { green_rock, green_rock, green_rock, green_rock, green_rock, green_rock, green_rock, 00, 00, 00, 00, 00 },
                    }
                };    

                pushLevel(&levelDef); 
            }    

            break;
        
        case g09 :             
            {
                levelDef = {
                    {
                        { 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00 },
                        { 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00 },
                        { 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00 },
                        { 00, 00, 00, green_tree, 00, 00, 00, green_tree, 00, 00, 00, 00 },
                        { 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00 },
                        { 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00 },
                        { 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00 },
                        { 00, 00, 00, green_tree, 00, 00, 00, green_tree, 00, 00, 00, 00 },
                        { 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00 },
                        { 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00 },
                    }
                };    

                pushLevel(&levelDef); 
            }    

            break;

        default:
            break;
    }    
}

void Level::pushLevel(std::array<std::array<int, 12>, 10> *levelDefPtr) {  
    std::array<std::array<int, 12>, 10> levelDef = *levelDefPtr;
    for (int i = 0; i < levelDef.size(); ++i) {
        for (int j = 0; j < levelDef[i].size(); ++j) {
            if(static_cast<SpriteType>(levelDef[i][j]) == empty) continue;                        
            spriteList.push_back(getSprite(static_cast<SpriteType>(levelDef[i][j]), j*spriteSize, i*spriteSize));
        }
    }
}

void Level::display() {
    SDL_SetRenderDrawColor(Core::getInstance()->getRender(), 252, 216, 168, 255);
    //SDL_RenderCopy(render, sdl_texture, &srcTextureParams, &destTextureParams);

    for (size_t i = 0; i < spriteList.size(); ++i) {
        this->spriteList[i]->display();
    }

    for (size_t i = 0; i < enemyList.size(); ++i) {
        this->enemyList[i]->display();
    }
}

void Level::cleanup() {
    //SDL_DestroyTexture(sdl_texture);

    /*for (size_t i = 0; i < spriteList.size(); ++i) {
        //this->spriteList[i]->display();
        SDL_DestroyTexture(this->spriteList[i]->sdl_texture);

    }

    for (size_t i = 0; i < enemyList.size(); ++i) {
        //this->enemyList[i]->display();
        SDL_DestroyTexture(this->enemyList[i]->sdl_texture);
    }*/
}
