#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <player.hpp>

Player::Player(SDL_Renderer *render) {
    this->render = render;

    /*
    int x the x location of the rectangle's upper left corner
    int y the y location of the rectangle's upper left corner
    int w the width of the rectangle
    int h the height of the rectangle
    */

    srcTextureParams = { 1, 11,  15, 16 }; // base front1
    //destTextureParams = { 235, 240,  50, 50 };
    //sdl_texture = IMG_LoadTexture(render, imagePath.c_str());
}

Player::~Player() { 
    cleanup();
}

void Player::position() {
    destTextureParams.h = 50;
    destTextureParams.w = 50;

    if(playerAction == swordFront1) destTextureParams.y += 50;
    if(playerAction == swordLeft1) destTextureParams.x +=50;  

    switch(playerDirection) {
        case down :             
            if(playerAction == front1) {
                srcTextureParams = { 18, 11,  15, 16 }; //front2
                playerAction = front2;
            } else if (playerAction == front2) {
                srcTextureParams = { 1, 11,  15, 16 }; // base front1
                playerAction = front1;
            } else {
                srcTextureParams = { 1, 11,  15, 16 }; // base front1
                playerAction = front2;
            }
            break;

        case up :    
            if(playerAction == back1) {
                srcTextureParams = { 87, 11,  15, 16 }; //back2
                playerAction = back2;
            } else if (playerAction == back2) {
                srcTextureParams = { 70, 11,  15, 16 }; // back1
                playerAction = back1;
            } else {
                srcTextureParams = { 70, 11,  15, 16 }; // back1
                playerAction = back2;
            } 
            break;

        case left : 
            if(playerAction == left1) {
                srcTextureParams = { 35, 11,  15, 16 }; //left2
                playerAction = left2;
            } else if (playerAction == left2) {
                srcTextureParams = { 52, 11,  15, 16 }; // left1
                playerAction = left1;
            } else {
                srcTextureParams = { 52, 11,  15, 16 }; // left1
                playerAction = left2;
            }
            break;

        case right : 
            if(playerAction == right1) {
                srcTextureParams = { 35, 11,  15, 16 }; //right2
                playerAction = front2;
            } else if (playerAction == right2) {
                srcTextureParams = { 52, 11,  15, 16 }; // right1
                playerAction = right1;
            } else {
                srcTextureParams = { 52, 11,  15, 16 }; // right1
                playerAction = right2;
            }
            break;
    }    
}

void Player::moveUp() {
    playerDirection = up;
    position();
    destTextureParams.y -= 10;
    playerFlip = SDL_FLIP_NONE;
}

void Player::moveDown() {
    playerDirection = down;
    position();
    destTextureParams.y += 10;
    playerFlip = SDL_FLIP_NONE;
}

void Player::moveRight() {    
    playerDirection = right;
    position();
    destTextureParams.x += 10;
    playerFlip = SDL_FLIP_NONE;
}

void Player::moveLeft() {
    playerDirection = left;
    position();
    destTextureParams.x -= 10;
    playerFlip = SDL_FLIP_HORIZONTAL;
}

void Player::attack() {
    switch(playerDirection) {
        case down : 
            srcTextureParams = { 18, 47,  15, 30 }; //down
            destTextureParams.h = 100;
            playerAction = swordBack1;
        break;

        case up : 
            srcTextureParams = { 18, 97,  15, 30 }; //up
            destTextureParams.h = 100;
            destTextureParams.y -= 50;
            playerAction = swordFront1;
        break;

        case left : 
            srcTextureParams = { 19, 78,  27, 15 }; //left
            destTextureParams.w = 100;
            destTextureParams.x -=50; 
            playerAction = swordLeft1;
        break;

        case right : 
            srcTextureParams = { 19, 78,  27, 15 }; //right
            destTextureParams.w = 100;
            playerAction = swordRight1;
        break;
    }
}

void Player::display() {
    //SDL_RenderCopy(render, sdl_texture, &srcTextureParams, &destTextureParams);
    SDL_RenderCopyEx(render, sdl_texture, &srcTextureParams ,&destTextureParams, 0.0, NULL, playerFlip);
}

void Player::cleanup() {
    SDL_DestroyTexture(sdl_texture);
}
