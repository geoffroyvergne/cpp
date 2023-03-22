#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "sdl-core.hpp"

void SdlCore::init(int width, int height) { 

    SDL_Log("Core init");

    // init sdl
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not initialize SDL: %s\n", SDL_GetError());
        
		exit(EXIT_FAILURE);
	}
    
    // init window
    window = SDL_CreateWindow(this->name.c_str(), 100, 100, width*size, height*size, SDL_WINDOW_RESIZABLE);
    if (window == NULL) {cleanup(); exit(EXIT_FAILURE);}

    // init render
    render = SDL_CreateRenderer(this->window, -1, 0);
    if (render == NULL) {cleanup(); exit(EXIT_FAILURE);}

    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);    
}

SdlCore* SdlCore::getInstance() {
    if(!SdlCore::instance) {
        SdlCore::instance = new SdlCore();
    }
    
    return instance;
}

SDL_Window* SdlCore::getWindow() {
    return window;
}

SDL_Renderer* SdlCore::getRender() {
    return render;
}

void SdlCore::cleanup() {
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
	SDL_Quit();
}

SdlCore* SdlCore::instance = nullptr;
