#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <player.hpp>
#include <core.hpp>

Player::Player() {

    /*
    int x the x location of the rectangle's upper left corner
    int y the y location of the rectangle's upper left corner
    int w the width of the rectangle
    int h the height of the rectangle
    */

    srcTextureParams = { 1, 11,  15, 16 }; // base front1
    //destTextureParams = { 235, 240,  50, 50 };
}

Player::~Player() { 
    cleanup();
}

/*
base,
    front1,
    front2,
    swordFront1,    
    left1,
    left2,
    swordLeft1,
    right1,
    right2,
    swordRight1,
    back1,
    back2,
    swordBack1,
*/

bool Player::isAttack() {
    switch(playerAction) {
        case swordFront1: case swordLeft1: case swordRight1: case swordBack1: 
            return true;
            break;
            
        default:
            break;
    }

    return false;
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

    //if(destTextureParams.y < -10) destTextureParams.y = 500;
}

void Player::moveDown() {
    playerDirection = down;
    position();
    destTextureParams.y += 10;
    playerFlip = SDL_FLIP_NONE;

    //if(destTextureParams.y > 500) destTextureParams.y = -10;
}

void Player::moveRight() {    
    playerDirection = right;
    position();
    destTextureParams.x += 10;
    playerFlip = SDL_FLIP_NONE;

    //if(destTextureParams.x > 522) destTextureParams.x = -10;
}

void Player::moveLeft() {
    playerDirection = left;
    position();
    destTextureParams.x -= 10;
    playerFlip = SDL_FLIP_HORIZONTAL;

    //if(destTextureParams.x < -10) destTextureParams.x = 522;
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
    SDL_RenderCopyEx(Core::getInstance()->getRender(), Core::getInstance()->getSdlTextureLink(), &srcTextureParams ,&destTextureParams, 0.0, NULL, playerFlip);
}

void Player::cleanup() {
    SDL_DestroyTexture(Core::getInstance()->getSdlTextureLink());
}
