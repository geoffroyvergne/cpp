#include <iostream>
#include <SDL.h>

#include <block-type.hpp>
#include <block-color.hpp>

#ifndef BLOCK
#define BLOCK

class Block {
    public:
        Block(SDL_Renderer *render, BlockType type);
        ~Block();
        
        std::string imagePath;
        BlockType type;
        BlockColor color;

        SDL_Renderer *render;
        SDL_Texture *sdl_texture;
        SDL_Rect textureParams;
        
        void moveUp();
        void moveDown();
        void moveRight();
        void moveLeft();

        void display();
        void cleanup();
};

#endif
