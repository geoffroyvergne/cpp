#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "singleton_init.hpp"

void SingletonInit::init() { 
    // init sdl
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not initialize SDL: %s\n", SDL_GetError());
        
		exit(EXIT_FAILURE);
	}
    
    // init window
    window = SDL_CreateWindow(this->name.c_str(), 100, 100, this->width, this->height, SDL_WINDOW_SHOWN);
    if (window == NULL) {cleanup(); exit(EXIT_FAILURE);}

    // init render
    render = SDL_CreateRenderer(this->window, -1, 0);
    if (render == NULL) {cleanup(); exit(EXIT_FAILURE);}

    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);

    // init texture
    sdl_texture = IMG_LoadTexture(this->render, this->imagePath.c_str());

    if(sdl_texture == NULL) {
        SDL_Log("sdl_texture NULL");
    }

    // init TTF messages
    TTF_Init();
}

SingletonInit* SingletonInit::getInstance() {
    if(!SingletonInit::instance) {
        SingletonInit::instance = new SingletonInit();
    }
    return instance;
}

SDL_Window* SingletonInit::getWindow() {
    return window;
}

SDL_Texture* SingletonInit::getSdlTexture() {
    return sdl_texture;
}

SDL_Renderer* SingletonInit::getRender() {
    return render;
}

void SingletonInit::displayMessage(int fontSize, SDL_Color color, SDL_Rect textureParams, std::string message) {     
    
    font = TTF_OpenFont(fontPath.c_str(), fontSize);
    //sdlSurface = TTF_RenderText_Blended(font, message.c_str(), color);
    sdlSurface = TTF_RenderText_Blended(font, message.c_str(), color);
    sdlTexture = SDL_CreateTextureFromSurface(SingletonInit::getInstance()->getRender(), sdlSurface);
    SDL_RenderCopy(SingletonInit::getInstance()->getRender(), sdlTexture, NULL, &textureParams);  

    //SDL_DestroyTexture(sdlTexture);
    //SDL_FreeSurface(sdlSurface);
}

void SingletonInit::cleanup() {
    TTF_CloseFont(font);    
    TTF_Quit();

    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
	SDL_Quit();
}

SingletonInit* SingletonInit::instance = nullptr;
