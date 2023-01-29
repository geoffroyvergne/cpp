#include <iostream>
#include <SDL.h>
#include <square.hpp>
#include <color.hpp>
#include <core.hpp>

Square::Square(Color color, int width, int id) { 
    this->width = width;
    this->id = id;    
    this->color = color;
    bool selected = false;

    switch(color) {
        case transparent : 
            srcTextureParams = { 0, 0, 10, 10 };
            colorStr = "transparent";
            break;

        case white : 
            srcTextureParams = { 100, 370, 10, 10 };
            colorStr = "white";
            break;

        case black :            
            srcTextureParams = { 40, 370, 10, 10 };
            colorStr = "black";
            break; 
    }

    //srcSelectedTextureParams = { 158, 360, 36, 33 };

    destTextureParams = { 50, 50,  width, width };
}

Square::~Square() { 
    cleanup();
}

void Square::display() {
    SDL_RenderCopy(Core::getInstance()->getRender(), Core::getInstance()->getSdlTexture(), &srcTextureParams, &destTextureParams);
    /*if(this->selected) {
        SDL_RenderCopy(Core::getInstance()->getRender(), Core::getInstance()->getSdlTexture(), &srcSelectedTextureParams, &destTextureParams);
    }*/
}

void Square::cleanup() {
    //SDL_DestroyTexture(Core::getInstance()->getSdlTexture());
}
