#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <plateau.hpp>
#include <snake.hpp>

Plateau::Plateau(SDL_Renderer *render, SDL_Texture *sdl_texture) {
    this->render = render;   
    this->currentBlockType = base; 
    this->sdl_texture = sdl_texture;
    
    /*if (sdl_texture == NULL){
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl_texture Error: %s\n", IMG_GetError());
		//return NULL;
	}*/

    this->addWall();
}

Plateau::~Plateau() {
    cleanup();
}

void Plateau::addSnake() {    
    snake = new Snake(this->render, this->sdl_texture);
}

void Plateau::addWall() {
    for(int i=0; i<16; i++) {
        Block *block = new Block(render, base, sdl_texture);
        block->destTextureParams.x = 0;
        block->destTextureParams.y = (i) * 50;

        wallList.push_back(block);
    }

    for(int i=0; i<16; i++) {
        Block *block = new Block(render, base, sdl_texture);
        block->destTextureParams.x = 500;
        block->destTextureParams.y = (i) * 50;

        wallList.push_back(block);
    }

    for(int i=0; i<9; i++) {
        Block *block = new Block(render, base, sdl_texture);
        block->destTextureParams.x = (i+1) * 50;
        block->destTextureParams.y = 750;

        wallList.push_back(block);
    }

    for(int i=0; i<9; i++) {
        Block *block = new Block(render, base, sdl_texture);
        block->destTextureParams.x = (i+1) * 50;
        block->destTextureParams.y = 0;

        wallList.push_back(block);
    }
}

void Plateau::display() {
    for (size_t i = 0; i < this->wallList.size(); ++i) {
        this->wallList[i]->display();
    }
}

void Plateau::cleanup() {
    for (size_t i = 0; i < this->wallList.size(); ++i) {
        this->wallList[i]->cleanup();
    }
}

