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

    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);

    // init texture
    sdl_texture_overworld = IMG_LoadTexture(this->render, this->imagePath_overworld.c_str());

    if(sdl_texture_overworld == NULL) {
        SDL_Log("sdl_texture_overworld NULL");
    }

    sdl_texture_overworld_enemies = IMG_LoadTexture(this->render, this->imagePath_overworld_enemies.c_str());

    if(sdl_texture_overworld_enemies == NULL) {
        SDL_Log("sdl_texture_overworld_enemies NULL");
    }

    sdl_texture_item = IMG_LoadTexture(this->render, this->imagePath_item.c_str());

    if(sdl_texture_item == NULL) {
        SDL_Log("sdl_texture_item NULL");
    }

    sdl_texture_link = IMG_LoadTexture(this->render, this->imagePath_link.c_str());

    if(sdl_texture_link == NULL) {
        SDL_Log("sdl_texture_link NULL");
    }

    // init TTF messages
    TTF_Init();
}

void Core::displayMessage(int fontSize, SDL_Color color, SDL_Rect textureParams, std::string message) {
    //SDL_Log("Display message");

    //font = TTF_OpenFont(fontPath.c_str(), fontSize);
    //sdlSurface = TTF_RenderText_Blended(font, message.c_str(), color);
    //sdlSurface = TTF_RenderText_Blended(font, message.c_str(), color);
    //sdlTexture = SDL_CreateTextureFromSurface(Core::getInstance()->getRender(), sdlSurface);
    //SDL_RenderCopy(Core::getInstance()->getRender(), sdlTexture, NULL, &textureParams);  

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

SDL_Texture* Core::getSdlTextureOverWorld() {
    return sdl_texture_overworld;
}

SDL_Texture* Core::getSdlTextureOverworldEnemies() {
    return sdl_texture_overworld_enemies;
}

SDL_Texture* Core::getSdlTextureItem() {
    return sdl_texture_item;
}

SDL_Texture* Core::getSdlTextureLink() {
    return sdl_texture_link;
}

SDL_Renderer* Core::getRender() {
    return render;
}

void Core::cleanup() {
    SDL_DestroyTexture(sdl_texture_overworld);
    SDL_DestroyTexture(sdl_texture_overworld_enemies);
    SDL_FreeSurface(sdlSurface);

    TTF_CloseFont(font);    
    TTF_Quit();

    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
	SDL_Quit();
}

Core* Core::instance = nullptr;
