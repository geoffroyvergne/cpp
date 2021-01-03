#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

#include <message.hpp>

Message::Message(SDL_Renderer *render) {
    
    this->render = render;

    TTF_Init();
    font = TTF_OpenFont(fontPath.c_str(), fontSize);
}

Message::~Message() { 
    cleanUp();
}

void Message::displayMessage() {     
    sdlSurface = TTF_RenderText_Blended(font, message.c_str(), color);
    sdlTexture = SDL_CreateTextureFromSurface(render, sdlSurface);
    SDL_RenderCopy(render, sdlTexture, NULL, &textureParams);  

    SDL_DestroyTexture(sdlTexture);
    SDL_FreeSurface(sdlSurface);
}

void Message::cleanUp() {    
    TTF_CloseFont(font);    
    TTF_Quit();
}

