#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include <array>
#include <vector>

#include <case.hpp>

#ifndef PLATEAU
#define PLATEAU

class Plateau {
    public:
        Plateau(SDL_Renderer *render, SDL_Texture *sdl_texture);
        ~Plateau();

        std::vector<Case*> caseList;

        void init();

        void display();
        void cleanup();
};

#endif