#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

#include <message.hpp>

Message::Message(SDL_Renderer *render, std::string fontPath) {
    
    this->render = render;
    this->fontPath = fontPath;

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
    //SDL_DestroyTexture(sdlTexture); 
    //SDL_FreeSurface(sdlSurface);
    
    //if(sdlTexture != nullptr) SDL_DestroyTexture(sdlTexture);
    //if(sdlSurface != nullptr) SDL_FreeSurface(sdlSurface);
    
    //if(font != nullptr) TTF_CloseFont(font);
}
