#include <iostream>
#include <SDL.h>
#include <vector>
#include <sprite.hpp>

#ifndef LEVEL
#define LEVEL

class Level {
    public:
        Level(SDL_Renderer *render);
        ~Level();
        std::string imagePath;
        std::vector<Sprite*> spriteList;

        SDL_Renderer *render;
        SDL_Texture *sdl_texture;
        SDL_Rect srcTextureParams; // Real texture size and placement
        SDL_Rect destTextureParams; // Texture seen in game

        //Level left;
        //Level right;
        //Level up;
        //Level down;
        void display();
        void cleanup();
};

#endif
