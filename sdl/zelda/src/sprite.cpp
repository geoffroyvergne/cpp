#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <sprite.hpp>

Sprite::Sprite(SDL_Renderer *render, SDL_Texture *sdl_texture) {
    this->render = render;
    this->sdl_texture = sdl_texture;

    srcTextureParams = { 1, 11,  15, 16 };
    destTextureParams = { 18, 11,  15, 16 };
}

Sprite::~Sprite() { 
    cleanup();
}

void Sprite::display() {
    SDL_RenderCopy(render, sdl_texture, &srcTextureParams, &destTextureParams);
}

void Sprite::cleanup() {
    SDL_DestroyTexture(sdl_texture);
}
