#include <iostream>
#include <SDL.h>

#ifndef GAME
#define GAME

class Game {
    public:
        int SCREEN_WIDTH  = 256;
        int SCREEN_HEIGHT = 240;
        SDL_Window *win;
        SDL_Renderer *ren;
        SDL_Texture *tex;
        void init();
        void cleanup(int status);
        void loadBackground(std::string file);
        void startLoop();
        SDL_Surface* loadImage(std::string file);
        SDL_Texture* renderSurface(SDL_Renderer *ren, SDL_Surface *img);
        SDL_Texture* loadTexture(std::string file, SDL_Renderer *ren);
};

#endif
