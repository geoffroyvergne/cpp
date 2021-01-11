#include <iostream>
#include <SDL.h>
#include <player-action.hpp>
#include <player-direction.hpp>
#include <enemy-type.hpp>

#ifndef ENEMY
#define ENEMY

class Enemy {
    public:
        Enemy(SDL_Renderer *render, SDL_Texture *sdl_texture);
        ~Enemy();
        EnemyType type;

        SDL_Renderer *render;
        SDL_Texture *sdl_texture;
        SDL_Rect srcTextureParams; // Real texture size and placement
        SDL_Rect destTextureParams = { 250, 250,  50, 50 }; // Texture seen in game
        SDL_RendererFlip flip = SDL_FLIP_NONE;

        bool collide = true;

        void position();

        void moveUp();
        void moveDown();
        void moveRight();
        void moveLeft();

        void display();
        void cleanup();
    };

#endif
