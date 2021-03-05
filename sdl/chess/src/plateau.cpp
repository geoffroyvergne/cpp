#include <iostream>
#include <SDL.h>
#include <plateau.hpp>

Plateau::Plateau(SDL_Renderer *render, SDL_Texture *sdl_texture) { 
    init();
}

Plateau::~Plateau() { 
    cleanup();
}

void Plateau::init() {

}

void Plateau::display() {
    //SDL_RenderCopyEx(render, sdl_texture, &srcTextureParams ,&destTextureParams, 0.0, NULL, playerFlip);
}

void Plateau::cleanup() {
    //SDL_DestroyTexture(sdl_texture);
}