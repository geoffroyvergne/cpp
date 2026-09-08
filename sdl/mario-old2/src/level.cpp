#include <iostream>
#include <SDL.h>
#include <array>

#include <level.hpp>
#include <world.hpp>
#include <tile.hpp>

Level::Level(World world) {     
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
            setLevelData(this->level00);
        break;

        case w11:
            setLevelData(this->level11);
        break;
    }
}

void Level::setLevelData(std::array<std::array<int, 100>, 17> levelDef) {

    for (int i = 0; i < levelDef.size(); ++i) {
        for (int j = 0; j < levelDef[i].size(); ++j) {
            if(static_cast<TileType>(levelDef[i][j]) == none) continue;
            
            Tile *tile = new Tile(static_cast<TileType>(levelDef[i][j]));           
            tile->destTextureParams = { j*tileSize, i*tileSize,  tileSize, tileSize };
            this->tileList.push_back(tile);
        }
    }
}

void Level::setIntro() {
   
}

bool Level::detectCollision(Player *player) {
    SDL_bool collision;

    for (size_t i = 0; i < tileList.size(); ++i) {
        if(this->tileList[i]->collide) {  
            if(SDL_HasIntersection(&this->tileList[i]->destTextureParams, &player->destTextureParams)) return true;
        }
    }

   return false;
}

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

/*void Level::setLevel00() {
    
}*/

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