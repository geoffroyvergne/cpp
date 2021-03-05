#include <iostream>
#include <SDL.h>
#include <square.hpp>
#include <color.hpp>

Square::Square(SDL_Renderer *render, SDL_Texture *sdl_texture, Color color, int width, int id) { 
    this->width = width;
    this->id = id;
    this->render = render;
    this->sdl_texture = sdl_texture;
    this->color = color;

    switch(color) {
        case transparent : 
            srcTextureParams = { 0, 0, 10, 10 };
            break;

        case white : 
            srcTextureParams = { 40, 370, 10, 10 };
            break;

        case black :
            srcTextureParams = { 100, 370, 10, 10 };
            break; 
    }

    destTextureParams = { 50, 50,  width, width };
}

Square::~Square() { 
    cleanup();
}

void Square::display() {
    SDL_RenderCopy(render, sdl_texture, &srcTextureParams, &destTextureParams);
}

void Square::cleanup() {
    SDL_DestroyTexture(sdl_texture);
}
