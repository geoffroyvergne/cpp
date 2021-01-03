#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

#include <message.hpp>

Message::Message(SDL_Renderer *render) {
    this->render = render;
    
    //TTF_Init();
    //SDL_Surface * surface = TTF_RenderText_Solid(font, message.c_str(), color);

    font = TTF_OpenFont(fontPath.c_str(), fontSize);
        
    //sdlSurface = TTF_RenderText_Blended(font, message.c_str(), color);
    //sdlTexture = SDL_CreateTextureFromSurface(render, sdlSurface);
}

void Message::displayMessage() { 
    //this->message = message;      
    //message = "TIC TAC TOE " + getScore() + " winner : " + getPlayer(lastWinner);
    
    sdlSurface = TTF_RenderText_Blended(font, message.c_str(), color);
    sdlTexture = SDL_CreateTextureFromSurface(render, sdlSurface);
    SDL_RenderCopy(render, sdlTexture, NULL, &textureParams);  

    cleanUp();
}

void Message::cleanUp() {
    //TTF_Quit();
    //TTF_CloseFont(font);
    SDL_DestroyTexture(sdlTexture);
    SDL_FreeSurface(sdlSurface);
}
