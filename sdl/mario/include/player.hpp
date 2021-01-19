#include <iostream>
#include <SDL.h>

#include <player-action.hpp>
#include <player-direction.hpp>

#ifndef PLAYER
#define PLAYER

class Player {
    public:
        Player(SDL_Renderer *render);
        ~Player();

        SDL_Renderer *render;
        SDL_Texture *sdl_texture;
        SDL_Rect srcTextureParams; // Real texture size and placement
        SDL_Rect destTextureParams; //= { 250, 250,  50, 50 }; // Texture seen in game
        SDL_RendererFlip playerFlip = SDL_FLIP_NONE;
        int tileSize = 30;

        PlayerAction playerAction = action_base;
        PlayerDirection playerDirection = direction_base;

        void position();
        void moveRight();
        void moveLeft();
        void moveUp(int gap);
        void moveDown(int gap);
        
        void walkRight();
        void walkLeft();

        void jump(int gap);
        void fall(int gap);

        void display();
        void cleanup();
};

#endif
