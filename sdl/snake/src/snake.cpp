#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <snake.hpp>
//#include <block.hpp>
#include <block-type.hpp>
//#include <plateau.hpp>
#include <direction.hpp>

Snake::Snake(SDL_Renderer *render, SDL_Texture *sdl_texture) {
    this->render = render;
    this->sdl_texture = sdl_texture;
    currentDirection = none;
}

Snake::~Snake() { 
    cleanup();
}

void Snake::addBlock(Block *block) {
     blockList.push_back(block);
}

void Snake::moveUp() {
    //if(currentDirection != up) {
        for (size_t i = 0; i < this->blockList.size(); ++i) {
            this->blockList[i]->destTextureParams.y -= 50;
        }
        currentDirection = up;
    //}
}

void Snake::moveDown() {
    //if(currentDirection != down) {
        for (size_t i = 0; i < this->blockList.size(); ++i) {
            this->blockList[i]->destTextureParams.y += 50;
        }
        currentDirection = down;
    //}
}

void Snake::moveRight() {
    //if(currentDirection != right) {
        for (size_t i = 0; i < this->blockList.size(); ++i) {
            this->blockList[i]->destTextureParams.x += 50;
        }
        currentDirection = right;
    //}
}

void Snake::moveLeft() {
    //if(currentDirection != left) {
        for (size_t i = 0; i < this->blockList.size(); ++i) {
            this->blockList[i]->destTextureParams.x -= 50;
        }
        currentDirection = left;
    //}
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
