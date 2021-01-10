#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <level.hpp>

Level::Level(SDL_Renderer *render) {
    this->render = render;

    //SDL_SetRenderDrawColor(render, 252, 216, 168, 255);
    //SDL_RenderClear(render);
	//SDL_RenderPresent(render); 
}

Level::~Level() { 
    cleanup();
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
