#include <iostream>
#include <SDL.h>
#include <cell.hpp>
#include <SDL2_gfxPrimitives.h>
#include <sdl-core.hpp>

Cell::Cell() {
    //this->state = state;
    setColor();
}

Cell::~Cell() { 
    //cleanup();
}

void Cell::display() {
    setColor();
    SDL_SetRenderDrawColor(SdlCore::getInstance()->getRender(), color.r, color.g, color.b, color.a);

    //SDL_Log("position.caseNumber %d position.x %d position.y %d", position.caseNumber, position.x, position.y);

    int x1 = position.x * SdlCore::getInstance()->size;
    int y1 = position.y * SdlCore::getInstance()->size;
    int x2 = SdlCore::getInstance()->size;
    int y2 = SdlCore::getInstance()->size;

    SDL_Rect rect = {x1, y1, x2, y2};
    SDL_RenderFillRect(SdlCore::getInstance()->getRender(), &rect);
}

void Cell::setColor() {
    switch(state) {
        /*case State::none:
            color = {200,200,200,255};
        break;*/

        case 0:
            color = {255,255,255,255};
        break;

        case 1:
            color = {0,0,0,255};
        break;
    }
}

void Cell::cleanup() {

}