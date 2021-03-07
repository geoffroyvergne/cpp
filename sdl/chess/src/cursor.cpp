#include <iostream>
#include <SDL.h>
#include <cursor.hpp>

Cursor::Cursor(SDL_Renderer *render, SDL_Texture *sdl_texture, int width, int border) {
    this->width = width;
    this->border = border;
    this->render = render;
    this->sdl_texture = sdl_texture;

    srcTextureParams = { 158, 360, 36, 33 };
    destTextureParams = { border + width*3, border + width*3, width, width };
}

Cursor::~Cursor() { 
    cleanup();
}

void Cursor::up() {
    if(destTextureParams.y > border) destTextureParams.y -=width;
}

void Cursor::down() {
    if(destTextureParams.y < border*9) destTextureParams.y +=width;
}

void Cursor::left() {
    if(destTextureParams.x > border) destTextureParams.x -=width;
}

void Cursor::right() {
    if(destTextureParams.x < border*9) destTextureParams.x +=width;
}

int Cursor::getId() {
    int x = (destTextureParams.x / border) -1;
    int y = (destTextureParams.y / border) -1;

    //SDL_Log("x : %d y : %d", x, y);

    int id = x + (y*8);

    return id;
}

void Cursor::display() {
    SDL_RenderCopy(render, sdl_texture, &srcTextureParams, &destTextureParams);    
}

void Cursor::cleanup() {
    SDL_DestroyTexture(sdl_texture);
}
