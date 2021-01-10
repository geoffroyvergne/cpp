#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#ifndef SPRITE
#define SPRITE

class Sprite {
    public:
        Sprite(SDL_Renderer *render, SDL_Texture *sdl_texture);
        ~Sprite();

        SDL_Renderer *render;
        SDL_Texture *sdl_texture;
        
        SDL_Rect srcTextureParams; // Real texture size and placement
        SDL_Rect destTextureParams = { 235, 240,  50, 50 }; // Texture seen in game
        bool collide = true;

        void display();
        void cleanup();
};

#endif
