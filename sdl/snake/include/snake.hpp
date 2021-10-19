#include <iostream>
#include <vector>
#include <SDL.h>

#include <block.hpp>
//#include <plateau.hpp>
#include <direction.hpp>

#ifndef SNAKE
#define SNAKE

class Snake {
    public:
        Snake(SDL_Renderer *render, SDL_Texture *sdl_texture);
        ~Snake();

        std::vector<Block*> blockList;
        SDL_Renderer *render;
        SDL_Texture *sdl_texture;
        Direction currentDirection;

        void addBlock(Block *block);

        void moveUp();
        void moveDown();
        void moveRight();
        void moveLeft();

        void display();
        void cleanup();
};

#endif
