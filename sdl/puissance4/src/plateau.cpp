#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include <plateau.hpp>

Plateau::Plateau(SDL_Renderer *render) {
    this->render = render;
    sdl_texture = IMG_LoadTexture(render, imagePath.c_str());
}

Plateau::~Plateau() {
    cleanup();
}

void Plateau::display() {
    SDL_RenderCopy(render, sdl_texture, NULL, &textureParams);
}

void Plateau::cleanup() {
    SDL_DestroyTexture(sdl_texture);
}

