#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <level.hpp>

Level::Level(SDL_Renderer *render, Levels number, SDL_Texture *sdl_texture) {
    this->render = render;
    this->number = number;
    this->sdl_texture = sdl_texture;

    //SDL_SetRenderDrawColor(render, 252, 216, 168, 255);
    //SDL_RenderClear(render);
	//SDL_RenderPresent(render); 
}

Level::~Level() { 
    cleanup();
}

bool Level::detectCollision(Player *player) {
    SDL_bool collision;

    for (size_t i = 0; i < spriteList.size(); ++i) {
        if(this->spriteList[i]->collide) {
            collision = SDL_HasIntersection(&this->spriteList[i]->destTextureParams, &player->destTextureParams);
            if(collision) return true;
        }
    }

    return false;
}

void Level::display() {
    SDL_SetRenderDrawColor(render, 252, 216, 168, 255);
    //SDL_RenderCopy(render, sdl_texture, &srcTextureParams, &destTextureParams);

    for (size_t i = 0; i < spriteList.size(); ++i) {
        this->spriteList[i]->display();
    }
}

void Level::cleanup() {
    SDL_DestroyTexture(sdl_texture);
}
