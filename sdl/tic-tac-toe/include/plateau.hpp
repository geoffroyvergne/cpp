#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#ifndef PLATEAU
#define PLATEAU

class Plateau {
    public:
        Plateau(SDL_Renderer *render);
        SDL_Renderer *render;
        std::string imagePath = "../assets/plateau.png";
        SDL_Texture *sdl_texture;
        SDL_Rect textureParams = { 0, 0,  512, 512 };
        void display();        
};

#endif