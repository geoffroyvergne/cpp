#include <iostream>
#include <SDL.h>

#include <block-type.hpp>
#include <block-color.hpp>

#include <direction.hpp>

#ifndef BLOCK
#define BLOCK

class Block {
    public:
        Block(BlockType type);
        ~Block();
        
        std::string imagePath;
        BlockType type;
        //BlockColor color;

        //Direction currentDirection;

        SDL_Rect srcTextureParams; // Real texture size and placement
        SDL_Rect destTextureParams = { 250, 250,  50, 50 }; // Texture seen in game

        void switchType(BlockType type);
        
        /*void moveUp();
        void moveDown();
        void moveRight();
        void moveLeft();

        void moveCurrentDirection();*/

        void display();
        void cleanup();
};

#endif
