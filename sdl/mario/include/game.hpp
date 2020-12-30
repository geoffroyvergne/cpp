#include <iostream>
#include <vector>
#include <SDL.h>
#include <settings.hpp>

#ifndef TEXTURE
#define TEXTURE

class Texture {
    public:
        SDL_Texture *texture;
        SDL_Rect params;
        int move;
};

#endif

#ifndef GAME
#define GAME

class Game {
    public:
        SDL_Window *window;
        SDL_Renderer *render;
        //SDL_Texture *cloudTexture;
        //SDL_Texture *bushTexture;
        std::vector<Texture> texturesList;
        void init(std::string windowTitle, int screenWidth, int screenHeight);
        void startLoop();
        void cleanup();
        SDL_Texture* loadTexture(std::string file);
        Texture* loadTexture(std::string file, SDL_Rect textureParams, int move);
        void renderSprite(SDL_Texture *texture, SDL_Rect *textureParams);
};

#endif
