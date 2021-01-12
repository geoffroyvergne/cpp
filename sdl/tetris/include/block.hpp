#include <iostream>
#include <SDL.h>

#include <block-type.hpp>
#include <block-color.hpp>

#ifndef BLOCK
#define BLOCK

class Block {
    public:
        Block(SDL_Renderer *render, BlockType type, SDL_Texture *sdl_texture);
        ~Block();
        
        std::string imagePath;
        BlockType type;
        BlockColor color;

        SDL_Renderer *render;
        SDL_Texture *sdl_texture;
        SDL_Rect srcTextureParams; // Real texture size and placement
        SDL_Rect destTextureParams = { 250, 250,  50, 50 }; // Texture seen in game
        //SDL_Rect textureParams;
        
        void moveUp();
        void moveDown();
        void moveRight();
        void moveLeft();

        void display();
        void cleanup();
};

#endif
