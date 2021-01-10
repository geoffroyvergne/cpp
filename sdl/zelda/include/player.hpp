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
        std::string name = "Link";
        //std::string imagePath = "../assets/link.png";

        SDL_Renderer *render;
        SDL_Texture *sdl_texture;
        SDL_Rect srcTextureParams; // Real texture size and placement
        SDL_Rect destTextureParams = { 235, 240,  50, 50 }; // Texture seen in game
        SDL_RendererFlip playerFlip = SDL_FLIP_NONE;

        PlayerAction playerAction = base;
        PlayerDirection playerDirection = down;

        //void moveSide();
        void moveUp();
        void position();
        void moveDown();
        void moveRight();
        void moveLeft();
        void attack();
        //void endAttack();

        void display();
        void cleanup();
    };

#endif
