#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <plateau.hpp>

Plateau::Plateau(SDL_Renderer *render) {
    this->render = render;
    sdl_texture = IMG_LoadTexture(render, imagePath.c_str());
}

void Plateau::display() {
    //SDL_RenderClear(render);
    SDL_RenderCopy(render, sdl_texture, NULL, &textureParams);
    //SDL_RenderPresent(render);
}
