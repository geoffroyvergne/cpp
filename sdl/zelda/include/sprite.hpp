#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <sprite-type.hpp>

#ifndef SPRITE
#define SPRITE

class Sprite {
    public:
        Sprite();
        ~Sprite();        
        
        SDL_Rect srcTextureParams; // Real texture size and placement
        SDL_Rect destTextureParams = { 235, 240,  50, 50 }; // Texture seen in game
        bool collide = true;

        SpriteType type;

        void display();
        void cleanup();
};

#endif
