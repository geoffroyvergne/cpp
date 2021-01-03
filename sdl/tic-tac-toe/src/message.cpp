#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

#include <message.hpp>

Message::Message(SDL_Renderer *render) {
    
    this->render = render;

    TTF_Init();
    font = TTF_OpenFont(fontPath.c_str(), fontSize);

    //sdlSurface = TTF_RenderText_Solid(font, message.c_str(), color);

    //sdlSurface = TTF_RenderText_Blended(font, message.c_str(), color);
    //sdlTexture = SDL_CreateTextureFromSurface(render, sdlSurface);
}

Message::~Message() { 
    cleanUp();
}

void Message::displayMessage() { 
    //this->message = message;      
    //message = "TIC TAC TOE " + getScore() + " winner : " + getPlayer(lastWinner);
    
    sdlSurface = TTF_RenderText_Blended(font, message.c_str(), color);
    sdlTexture = SDL_CreateTextureFromSurface(render, sdlSurface);
    SDL_RenderCopy(render, sdlTexture, NULL, &textureParams);  

    SDL_DestroyTexture(sdlTexture);
    SDL_FreeSurface(sdlSurface);
}

void Message::cleanUp() {    
    TTF_CloseFont(font);
    //if(sdlTexture != NULL) SDL_DestroyTexture(sdlTexture);
    //if(sdlSurface != NULL) SDL_FreeSurface(sdlSurface);

    TTF_Quit();
}
