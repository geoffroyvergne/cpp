#include <iostream>
#include <SDL.h>
#include <array>

#include <level.hpp>
#include <world.hpp>
#include <tile.hpp>

Level::Level(World world, SDL_Renderer *render, SDL_Texture *sdl_texture_levels, SDL_Texture *sdl_texture_enemies) { 
    this->world = world;
    this->render = render;
    this->sdl_texture_levels = sdl_texture_levels;
    this->sdl_texture_enemies = sdl_texture_enemies;
    this->setLevel(world);
}

Level::~Level() { 
    cleanUp();
}

void Level::setLevel(World world) {
    switch(world) {
        case intro:
            setIntro();
        break;

        case w00:
            setLevel00();
        break;

        case w11:
            setLevel11();
        break;
    }
}

void Level::setIntro() {
   
}

bool Level::detectCollision(Player *player) {
    SDL_bool collision;

    for (size_t i = 0; i < tileList.size(); ++i) {
        if(this->tileList[i]->collide) {  
            //if(SDL_HasIntersection(&this->tileList[i]->destTextureParams, &player->destTextureParams)) return true;

            if(player->playerDirection == up) {
                this->tileList[i]->destTextureParams.y++;
                collision = SDL_HasIntersection(&this->tileList[i]->destTextureParams, &player->destTextureParams);
                this->tileList[i]->destTextureParams.y--;

                if( collision ) return true;
            } /*else if(player->playerDirection == down) {
                if(this->tileList[i]->destTextureParams.y + this->tileList[i]->destTextureParams.h == player->destTextureParams.y) return true;
            }*/ else {
                collision = SDL_HasIntersection(&this->tileList[i]->destTextureParams, &player->destTextureParams);
                if( collision ) return true;
            }

            /*if(player->playerDirection == left) {
                this->tileList[i]->destTextureParams.x++;
                collision = SDL_HasIntersection(&this->tileList[i]->destTextureParams, &player->destTextureParams);
                this->tileList[i]->destTextureParams.x--;
                if( collision ) return true;
            }

            if(player->playerDirection == right) {
                this->tileList[i]->destTextureParams.x--;
                collision = SDL_HasIntersection(&this->tileList[i]->destTextureParams, &player->destTextureParams);
                this->tileList[i]->destTextureParams.x++;
                if( collision ) return true;
            }*/
        }
    }

   return false;
}

/*bool Level::detectCollision(Player *player) {
    SDL_bool collision;

    for (size_t i = 0; i < tileList.size(); ++i) {
        if(this->tileList[i]->collide) {  
            if(SDL_HasIntersection(&this->tileList[i]->destTextureParams, &player->destTextureParams)) return true;
        }
    }

   return false;
}*/

void Level::moveRight() {
    for(auto tile : this->tileList) {
        tile->destTextureParams.x -= tileSize/2;
    }
}

void Level::moveLeft() {
    for(auto tile : this->tileList) {
        tile->destTextureParams.x += tileSize/2;
    }
}

void Level::setLevel00() {
    
}

void Level::setLevel11() {

    std::array<std::array<int, 30>, 17> levelDef = {
        {
            { 00,       00,     00,         00,         00,         00,         00,     cloud_ul,       cloud_uc,       cloud_uc,   cloud_ur,   00,         00, 00,         00,         00,         00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, },
            { 00,       00,     00,         cloud_ul,   cloud_uc,   cloud_ur,   00,     cloud_ll,       cloud_lc,       cloud_lc,   cloud_lr,   00,         00, 00,         00,         00,         00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, },
            { 00,       00,     00,         cloud_ll,   cloud_lc,   cloud_lr,   00,     00,             00,             00,         00,         00,         00, 00,         00,         00,         00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, },
            { 00,       00,     00,         00,         00,         00,         00,     00,             00,             00,         00,         00,         00, cloud_ul,   cloud_uc,   cloud_ur,   00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, },
            { 00,       00,     00,         00,         00,         00,         00,     00,             00,             00,         00,         00,         00, cloud_ll,   cloud_lc,   cloud_lr,   00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, },
            { 00,       00,     00,         00,         00,         00,         00,     03,             00,             00,         00,         00,         00, 00,         00,         00,         00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, },
            { 00,       00,     00,         00,         00,         00,         00,     00,             00,             00,         00,         00,         00, 00,         00,         00,         00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00,  },
            { 00,       00,     00,         00,         00,         00,         00,     00,             00,             00,         00,         00,         00, 00,         00,         00,         00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00,  },
            { 00,       00,     00,         00,         00,         00,         00,     00,             00,             00,         00,         00,         00, 00,         00,         00,         00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00,  },
            { 00,       00,     00,         00,         00,         00,         00,     00,             00,             00,         00,         00,         00, 00,         00,         00,         00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00,  },            
            { 00,       00,     00,         03,         00,         brick,      03,     brick,          03,             brick,      00,         00,         00, 00,         00,         00,         00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00,  },
            { 00,       00,     00,         00,         00,         00,         00,     00,             00,             00,         00,         00,         00, 00,         00,         00,         00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00,  },
            { 00,       00,     00,         00,         00,         00,         00,     00,             00,             00,         00,         00,         00, 00,         00,         00,         00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00,  },
            { 00,       00,     hill_t,     00,         00,         00,         00,     00,             00,             00,         pipe_ul,    pipe_ur,    00, 00,         00,         00,         00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00,  },
            { 00,       hill_l, hill_cs,    hill_r,     00,         00,         bush_l, bush_c,         bush_r,         00,         pipe_ll,    pipe_lr,    00, 00,         00,         00,         00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00,  },
            { 01,       01,     01,         01,         01,         01,         01,     01,             01,             01,         01,         01,         01, 01,         01,         01,         01, 00, 00, 00, 00, 01, 01, 01, 01, 01, 01, 01, 01, 01,  },
            { 01,       01,     01,         01,         01,         01,         01,     01,             01,             01,         01,         01,         01, 01,         01,         01,         01, 00, 00, 00, 00, 01, 01, 01, 01, 01, 01, 01, 01, 01,  },
        }
    };

    for (int i = 0; i < levelDef.size(); ++i) {
        for (int j = 0; j < levelDef[i].size(); ++j) {
            if(static_cast<TileType>(levelDef[i][j]) == none) continue;
            
            Tile *tile = new Tile(static_cast<TileType>(levelDef[i][j]), render, sdl_texture_levels);           
            tile->destTextureParams = { j*tileSize, i*tileSize,  tileSize, tileSize };
            this->tileList.push_back(tile);
        }
    }
}

std::string Level::getLevelName() {
    return "1-1";
}

void Level::display() {
    for(auto tile : this->tileList) {
        tile->display();
    }
}

void Level::cleanUp() {

}