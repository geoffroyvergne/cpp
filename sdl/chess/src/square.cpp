#include <iostream>
#include <SDL.h>
#include <square.hpp>
#include <color.hpp>
#include <sdl-core.hpp>

Square::Square(Color color, int id) {     
    this->id = id;    
    this->color = color;
    bool selected = false;

    switch(color) {
        case transparent : 
            colorStr = "transparent";
            sdlColor = {0,0,0,0};
            break;

        case white : 
            colorStr = "white";
            sdlColor = {255,255,255,255};
            break;

        case black :            
            colorStr = "black";
            sdlColor = {100,100,100,255};
            break;
        
        case red :
            colorStr = "selected";
            sdlColor = {128,0,0,100};
            break;
    }
}

Square::~Square() { 
    cleanup();
}

void Square::display() {

    SDL_SetRenderDrawColor(SdlCore::getInstance()->getRender(), sdlColor.r, sdlColor.g, sdlColor.b, sdlColor.a);

    int x1 = x * SdlCore::getInstance()->size;
    int y1 = y * SdlCore::getInstance()->size;
    int x2 = SdlCore::getInstance()->size;
    int y2 = SdlCore::getInstance()->size;

    SDL_Rect rect = {x1, y1, x2, y2};
    SDL_RenderFillRect(SdlCore::getInstance()->getRender(), &rect);
}

void Square::cleanup() {
    //SDL_DestroyTexture(Core::getInstance()->getSdlTexture());
}
