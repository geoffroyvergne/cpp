#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <piece.hpp>

Piece::Piece(SDL_Renderer *render, PieceType pieceype) {
    this->render = render;

    switch(pieceype) {
        case black_circle : 
            imagePath = "../assets/black-circle.png"; 
            player = circle;
            break;

        case black_cross : 
            imagePath = "../assets/black-cross.png"; 
            player = cross;
            break;

        case red_circle : 
            imagePath = "../assets/red-circle.png"; 
            player = circle;
            break;

        case red_cross : 
            imagePath = "../assets/red-cross.png"; 
            player = cross;
            break;
    }
    sdl_texture = IMG_LoadTexture(render, imagePath.c_str());
}

void Piece::getCaseNumberByTextureParams() {
    // 30 210 390

    if(textureParams.x == 30 && textureParams.y == 30) {
        caseNumber = 0;
    }

    if(textureParams.x == 210 && textureParams.y == 30) {
        caseNumber = 1;
    }

    if(textureParams.x == 390 && textureParams.y == 30) {
        caseNumber = 2;
    }

    if(textureParams.x == 30 && textureParams.y == 210) {
        caseNumber = 3;
    }

    if(textureParams.x == 210 && textureParams.y == 210) {
        caseNumber = 4;
    }

    if(textureParams.x == 390 && textureParams.y == 210) {
        caseNumber = 5;
    }

    if(textureParams.x == 30 && textureParams.y == 390) {
        caseNumber = 6;
    }

    if(textureParams.x == 210 && textureParams.y == 390) {
        caseNumber = 7;
    }

    if(textureParams.x == 390 && textureParams.y == 390) {
        caseNumber = 8;
    }
}

void Piece::display() {
    SDL_RenderCopy(render, sdl_texture, NULL, &textureParams);
}

void Piece::moveUp() {
    if(textureParams.y >30) textureParams.y -= 180;
}

void Piece::moveDown() {
    if(textureParams.y <390) textureParams.y += 180;
}

void Piece::moveRight() {
    if(textureParams.x <390) textureParams.x += 180;
}


void Piece::moveLeft() {
    if(textureParams.x >30) textureParams.x -= 180;
}