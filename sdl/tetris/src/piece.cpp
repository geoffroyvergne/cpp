#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <piece.hpp>
#include <block.hpp>
#include <block-type.hpp>

Piece::Piece(SDL_Renderer *render, BlockType type) {
    this->render = render;

}

Piece::~Piece() { 
    cleanup();
}

void Piece::addBlock(Block *block) {

}

void Piece::display() {

}

void Piece::cleanup() {
    
}