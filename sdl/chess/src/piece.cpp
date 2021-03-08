#include <iostream>
#include <SDL.h>
#include <piece.hpp>
#include <color.hpp>

Piece::Piece(SDL_Renderer *render, SDL_Texture *sdl_texture, PieceType type, Color color, int width, int border) {
    this->width = width;
    this->border = border;
    this->color = color;
    this->render = render;
    this->sdl_texture = sdl_texture;
    this->type = type;

    init();
}

void Piece::init() {
    //srcTextureParams = { 514, 17, 70, 70 };

    switch(type) {
        case none : 
            srcTextureParams = { 0, 0, 10, 10 };
            this->name = "none";
            break;

        case king :
            srcTextureParams = { 395, 20, 130, 130 };
            this->name = "king";
            break; 

        case queen :
            srcTextureParams = { 263, 20, 130, 130 };
            this->name = "queen";
            break; 

        case rook :
            srcTextureParams = { -5, 20, 130, 130 };
            this->name = "rook";
            break; 

        case bishop :
            srcTextureParams = { 128, 20, 130, 130 };
            this->name = "bishop";
            break; 

        case knight :
            srcTextureParams = { 530, 20, 130, 130 };
            this->name = "knight";
            break; 

        case paw :
            srcTextureParams = { 670, 25, 120, 120 };
            this->name = "paw";
            break; 
    }

    switch(color) {
        case white :
            srcTextureParams.y += 160;
            this->colorStr = "white";
            break;
        
        case black : 
            this->colorStr = "black";
            break;

        case transparent : 
            this-> colorStr = "transparent";
            break;
    }

    destTextureParams = { 50, 50,  width, width };
}
 
Piece::~Piece() { 
    cleanup();
}

bool Piece::validateMove(int currentId, int newId) {
    //TODO implement
    return true;
}

int Piece::calculateNewId() {
    int x = (destTextureParams.x / border) -1;
    int y = (destTextureParams.y / border) -1;

    //SDL_Log("x : %d y : %d", x, y);

    return x + (y*8);
}

void Piece::setId(int id) {
    this->id = id;
}

void Piece::setDestTextureParam(int id) {

    int x=0;
    int y=0;
    
    int i=0;
    while(i<id) {
        
        if(x>7) {
            y++; x=0;
        }

        x++;
        i++;
    }

    SDL_Log("id : %d x: %d y: %d", id, x, y);

    destTextureParams.x = (x+1) * border;
    destTextureParams.y = (y+1) * border;
}

void Piece::up() {
    if(destTextureParams.y > border) destTextureParams.y -=width;
}

void Piece::down() {
    if(destTextureParams.y < border*9) destTextureParams.y +=width;
}

void Piece::left() {
    if(destTextureParams.x > border) destTextureParams.x -=width;
}

void Piece::right() {
    if(destTextureParams.x < border*9) destTextureParams.x +=width;
}

void Piece::display() {
    SDL_RenderCopy(render, sdl_texture, &srcTextureParams, &destTextureParams);
}

void Piece::cleanup() {
    //SDL_DestroyTexture(sdl_texture);
}
