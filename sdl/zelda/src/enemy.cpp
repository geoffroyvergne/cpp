#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <enemy.hpp>
#include <enemy-type.hpp>
#include <core.hpp>

Enemy::Enemy() {    
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
    //SDL_RenderCopy(Core::getInstance()->getRender(), Core::getInstance()->getSdlTextureOverworldEnemies()->getSdlTextureOverworldEnemies(), &srcTextureParams, &destTextureParams);
    SDL_RenderCopyEx(Core::getInstance()->getRender(), Core::getInstance()->getSdlTextureOverworldEnemies(), &srcTextureParams ,&destTextureParams, 0.0, NULL, flip);
}

void Enemy::cleanup() {
    //SDL_DestroyTexture(Core::getInstance()->getSdlTextureOverworldEnemies());
}