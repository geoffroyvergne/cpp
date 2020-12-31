#include <iostream>
#include <vector>
#include <SDL.h>
#include <settings.hpp>
#include <texture.hpp>

#ifndef GAME
#define GAME

class Game {
    public:
        SDL_Window *window;
        SDL_Renderer *render;
        SDL_bool collision;
        std::vector<Texture> texturesList;
        Texture *marioTexture;
        void init(std::string windowTitle, int screenWidth, int screenHeight);
        void startLoop();
        void cleanup();
        Texture* loadTexture(std::string file, std::string name, SDL_Rect textureParams, int move, int colide);
        void loadLevel(int level);
        void loadLevelSprites(SDL_Event *e);
        void loadMarioSprite(SDL_Event *e, SDL_RendererFlip *marioFlip);
};

#endif
