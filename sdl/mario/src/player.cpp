#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <player.hpp>

Player::Player(SDL_Renderer *render) {
    this->render = render;

    destTextureParams = { 200, tileSize*14,  tileSize, tileSize };
    this->position();
}

Player::~Player() { 
    cleanup();
}

void Player::position() {
    switch(playerDirection) {
        case direction_base :  
            srcTextureParams = { 2, 8,  15, 16 }; //direction_base
            playerAction = action_base; 
            destTextureParams.y = tileSize*14;    
        break;

        case up :              
            srcTextureParams = { 119, 8,  15, 16 }; //action_jump
            playerAction = action_jump;            
        break;

        case down :              
            srcTextureParams = { 2, 8,  15, 16 };
            playerAction = action_base;
        break;

        case right : 
            if(playerAction == right1) {
                srcTextureParams = { 41, 8,  15, 16 }; //left2
                playerAction = right2;
            } else if (playerAction == right2) {
                srcTextureParams = { 58, 8,  15, 16 }; // left1
                playerAction = right1;
            } else {
                srcTextureParams = { 41, 8,  15, 16 }; // left1
                playerAction = right2;
            }
            break;
        break;

        case left : 
            if(playerAction == left1) {
                srcTextureParams = { 41, 8,  15, 16 }; //left2
                playerAction = left2;
            } else if (playerAction == left2) {
                srcTextureParams = { 58, 8,  15, 16 }; // left1
                playerAction = left1;
            } else {
                srcTextureParams = { 41, 8,  15, 16 }; // left1
                playerAction = left2;
            }
            break;
        break;
    }
}

void Player::moveRight() {  
    playerDirection = right;
    playerFlip = SDL_FLIP_NONE;
}

void Player::moveLeft() {
    playerDirection = left;
    playerFlip = SDL_FLIP_HORIZONTAL;
}

void Player::moveDown(int gap) {  
    playerDirection = down;
    destTextureParams.y += gap;
}

void Player::moveUp(int gap) {  
    playerDirection = up;
    destTextureParams.y -= gap;
}

void Player::walkRight() {
    this->moveRight();
    position();
}

void Player::walkLeft() {
    this->moveLeft();
    position();
}

void Player::jump(int gap) {
    moveUp(gap);
    position();
}

void Player::fall(int gap) {
    moveDown(gap);
    position();
}

void Player::display() {
    SDL_RenderCopyEx(render, sdl_texture, &srcTextureParams ,&destTextureParams, 0.0, NULL, playerFlip);
}

void Player::cleanup() {
    SDL_DestroyTexture(sdl_texture);
}
