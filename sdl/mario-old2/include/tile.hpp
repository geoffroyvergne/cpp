#include <iostream>
#include <SDL.h>
#include <tile-type.hpp>

#ifndef TILE
#define TILE

class Tile {
    public:
        Tile(TileType tileType);
        ~Tile();
       
        SDL_Rect srcTextureParams; // Real texture size and placement
        SDL_Rect destTextureParams; // Texture seen in game
        SDL_RendererFlip flip = SDL_FLIP_NONE;
        TileType tileType;

        bool collide = false;

        void display();
        void cleanUp();
};

#endif
