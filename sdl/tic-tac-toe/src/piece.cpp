#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <piece.hpp>

Piece::Piece(SDL_Renderer *render, PieceType pieceype, SDL_Texture *sdl_texture) {
    this->render = render;
    this->sdl_texture = sdl_texture;

    srcTextureParams = { 30, 30,  90, 90 };
    destTextureParams = { 30, 30,  90, 90 };

    this->togglePlayer(pieceype);
}

Piece::~Piece() { 
    cleanup();
}

void Piece::togglePlayer(PieceType pieceype) {
    switch(pieceype) {
        case black_circle : 
            //imagePath = "../assets/black-circle.png"; 
            srcTextureParams.x = 32;
            srcTextureParams.y = 26;
            player = circle;
            break;

        case black_cross : 
            //imagePath = "../assets/black-cross.png"; 
            srcTextureParams.x = 135;
            srcTextureParams.y = 20;
            player = cross;
            break;

        case red_circle : 
            //imagePath = "../assets/red-circle.png"; 
            srcTextureParams.x = 259;
            srcTextureParams.y = 22;
            player = circle;
            break;

        case red_cross : 
            //imagePath = "../assets/red-cross.png"; 
            srcTextureParams.x = 393;
            srcTextureParams.y = 23;
            player = cross;
            break;
    }

    //if(sdl_texture != NULL) SDL_DestroyTexture(sdl_texture);
    //sdl_texture = IMG_LoadTexture(render, imagePath.c_str());
}

void Piece::toggleColor() {
    //TODO Implement
}

void Piece::getCaseNumberByTextureParams() {
    // 30 210 390

    if(srcTextureParams.x == 30 && srcTextureParams.y == 30) {
        caseNumber = 0;
    }

    if(srcTextureParams.x == 210 && srcTextureParams.y == 30) {
        caseNumber = 1;
    }

    if(srcTextureParams.x == 390 && srcTextureParams.y == 30) {
        caseNumber = 2;
    }

    if(srcTextureParams.x == 30 && srcTextureParams.y == 210) {
        caseNumber = 3;
    }

    if(srcTextureParams.x == 210 && srcTextureParams.y == 210) {
        caseNumber = 4;
    }

    if(srcTextureParams.x == 390 && srcTextureParams.y == 210) {
        caseNumber = 5;
    }

    if(srcTextureParams.x == 30 && srcTextureParams.y == 390) {
        caseNumber = 6;
    }

    if(srcTextureParams.x == 210 && srcTextureParams.y == 390) {
        caseNumber = 7;
    }

    if(srcTextureParams.x == 390 && srcTextureParams.y == 390) {
        caseNumber = 8;
    }
}

void Piece::display() {
    //SDL_RenderCopy(render, sdl_texture, NULL, &srcTextureParams);
    SDL_RenderCopy(render, sdl_texture, &srcTextureParams, &destTextureParams);
}

void Piece::moveUp() {
    if(destTextureParams.y >30) destTextureParams.y -= 180;
}

void Piece::moveDown() {
    if(destTextureParams.y <390) destTextureParams.y += 180;
}

void Piece::moveRight() {
    if(destTextureParams.x <390) destTextureParams.x += 180;
}


void Piece::moveLeft() {
    if(destTextureParams.x >30) destTextureParams.x -= 180;
}

void Piece::cleanup() {
    SDL_DestroyTexture(sdl_texture);
}