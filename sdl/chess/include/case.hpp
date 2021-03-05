#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <case-type.hpp>
#include <case-position.hpp>

#ifndef CASE
#define CASE

class Case {
    public:
        Case(SDL_Renderer *render, SDL_Texture *sdl_texture);
        ~Case();
        CaseType type;
        CasePosition position;

        SDL_Renderer *render;
        SDL_Texture *sdl_texture;
        SDL_Rect srcTextureParams; // Real texture size and placement
        SDL_Rect destTextureParams = { 250, 250,  50, 50 }; // Texture seen in game

        void display();
        void cleanup();
};

#endif