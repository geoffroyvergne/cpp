#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "core.hpp"

void Core::init() { 

    SDL_Log("Core init");

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

    SDL_SetRenderDrawColor(render, 4, 156, 216, 255);

    // init texture    
    this->sdl_texture_player = IMG_LoadTexture(render, "../assets/player.png");   

    if(sdl_texture_player == NULL) {
        SDL_Log("sdl_texture_player NULL");
    }

    this->sdl_texture_levels = IMG_LoadTexture(render, "../assets/levels.png");

    if(sdl_texture_levels == NULL) {
        SDL_Log("sdl_texture_levels NULL");
    }

    this->sdl_texture_enemies = IMG_LoadTexture(render, "../assets/enemies.png");

    if(sdl_texture_enemies == NULL) {
        SDL_Log("sdl_texture_enemies NULL");
    }

    // init TTF messages
    TTF_Init();
}

void Core::displayMessage(int fontSize, SDL_Color color, SDL_Rect textureParams, std::string message) {
    //SDL_Log("Display message");

    /*font = TTF_OpenFont(fontPath.c_str(), fontSize);
    sdlSurface = TTF_RenderText_Blended(font, message.c_str(), color);
    sdlTexture = SDL_CreateTextureFromSurface(Core::getInstance()->getRender(), sdlSurface);
    SDL_RenderCopy(Core::getInstance()->getRender(), sdlTexture, NULL, &textureParams);*/

    //SDL_DestroyTexture(sdlTexture);
    //SDL_FreeSurface(sdlSurface);
}

Core* Core::getInstance() {
    if(!Core::instance) {
        Core::instance = new Core();
    }
    return instance;
}

SDL_Window* Core::getWindow() {
    return window;
}

SDL_Texture* Core::getSdlTexturePlayer() {
    return sdl_texture_player;
}

SDL_Texture* Core::getSdlTextureLevels() {
    return sdl_texture_levels;
}

SDL_Texture* Core::getSdlTextureEnemies() {
    return sdl_texture_enemies;
}

SDL_Renderer* Core::getRender() {
    return render;
}

void Core::cleanup() {
    SDL_DestroyTexture(sdl_texture_player);
    SDL_DestroyTexture(sdl_texture_levels);
    SDL_DestroyTexture(sdl_texture_enemies);

    SDL_FreeSurface(sdlSurface);

    TTF_CloseFont(font);    
    TTF_Quit();

    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
	SDL_Quit();
}

Core* Core::instance = nullptr;
