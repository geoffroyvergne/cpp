#include <iostream>
#include <SDL.h>
#include <player-action.hpp>
#include <player-direction.hpp>
#include <enemy-type.hpp>

#ifndef ENEMY
#define ENEMY

class Enemy {
    public:
        Enemy();
        ~Enemy();
        EnemyType type;
        
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
