#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <enemy.hpp>
#include <enemy-type.hpp>

Enemy::Enemy(SDL_Renderer *render, SDL_Texture *sdl_texture) {
    this->render = render;
    this->sdl_texture = sdl_texture;

    /*
    int x the x location of the rectangle's upper left corner
    int y the y location of the rectangle's upper left corner
    int w the width of the rectangle
    int h the height of the rectangle
    */

    switch(type) {
        case red_octorok : 
            srcTextureParams = { 1, 11,  15, 16 }; // base front1
            break;
    }
    //destTextureParams = { 235, 240,  50, 50 };
    //sdl_texture = IMG_LoadTexture(render, imagePath.c_str());
}

Enemy::~Enemy() { 
    cleanup();
}

void Enemy::position() {

}

void Enemy::moveUp() {

}

void Enemy::moveDown() {

}

void Enemy::moveRight() {  

}

void Enemy::moveLeft() {

}

void Enemy::display() {
    //SDL_RenderCopy(render, sdl_texture, &srcTextureParams, &destTextureParams);
    SDL_RenderCopyEx(render, sdl_texture, &srcTextureParams ,&destTextureParams, 0.0, NULL, flip);
}

void Enemy::cleanup() {
    //SDL_DestroyTexture(sdl_texture);
}