#include <iostream>
#include <SDL.h>

#ifndef TEXTURE
#define TEXTURE

class Texture {
    public:
        std::string name;
        SDL_Texture *texture;
        SDL_Rect params;
        int move;
        int colide;
};

#endif