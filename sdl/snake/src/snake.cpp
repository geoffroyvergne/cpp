#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <snake.hpp>
//#include <block.hpp>
#include <block-type.hpp>
//#include <plateau.hpp>

Snake::Snake(SDL_Renderer *render, SDL_Texture *sdl_texture) {
    this->render = render;
    this->sdl_texture = sdl_texture;

}

Snake::~Snake() { 
    cleanup();
}

void Snake::addBlock(Block *block) {
     blockList.push_back(block);
}

void Snake::display() {
    for (size_t i = 0; i < this->blockList.size(); ++i) {
        this->blockList[i]->display();
    }
}

void Snake::cleanup() {
    for (size_t i = 0; i < this->blockList.size(); ++i) {
        this->blockList[i]->cleanup();
    }
}
