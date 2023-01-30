#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <block.hpp>
#include <snake.hpp>

#ifndef PLATEAU
#define PLATEAU

class Plateau {
    public:
        Plateau();
        ~Plateau();
        std::vector<Block*> wallList;        
        BlockType currentBlockType;
        Snake *snake;

        //SDL_Renderer *render;
        //SDL_Texture *sdl_texture;

        void addSnake();
        
        void display();
        void cleanup();
        void addWall();        
};

#endif
