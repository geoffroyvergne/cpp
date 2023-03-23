#include <iostream>
#include <SDL.h>
#include <cursor.hpp>
#include <sdl-core.hpp>

Cursor::Cursor() {
    
}

Cursor::~Cursor() { 
    cleanup();
}

void Cursor::up() {
    if(y >0) y--;
}

void Cursor::down() {
    if(y <7) y++;
}

void Cursor::left() {
    if(x >0) x--;
}

void Cursor::right() {
    if(x <7) x++;
}

void Cursor::display() {
    SDL_SetRenderDrawColor(SdlCore::getInstance()->getRender(), sdlColor.r, sdlColor.g, sdlColor.b, sdlColor.a);

    int x1 = x * SdlCore::getInstance()->size;
    int y1 = y * SdlCore::getInstance()->size;
    int x2 = SdlCore::getInstance()->size;
    int y2 = SdlCore::getInstance()->size;

    SDL_Rect rect = {x1, y1, x2, y2};
    SDL_RenderFillRect(SdlCore::getInstance()->getRender(), &rect);
}

void Cursor::cleanup() {
}
