#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#ifndef CORE
#define CORE

class Core {
    private:
        static Core* instance;
        Core() {} //private constructor
        //Core();
        Core(const Core&) = delete; // copy constructor
        Core& operator=(const Core&) = delete; // assignment operator

        std::string imagePathLevels = "../assets/../assets/levels.png";
        std::string imagePathEnemies = "../assets/assets/enemies.png"; 
        std::string imagePathPlayer = "../assets/assets/player.png";             

        std::string fontPath = "../assets/arial.ttf";

        SDL_Window *window;
        SDL_Renderer *render;
        SDL_Texture *sdl_texture_levels;
        SDL_Texture *sdl_texture_enemies;
        SDL_Texture *sdl_texture_player;

        TTF_Font * font;
        SDL_Surface * sdlSurface;

    public:
        std::string name = "Mario";
        int height = 500;
        int width = 600;
        int loopDelay = 100;

        static Core* getInstance();
        void init();

        SDL_Window* getWindow();
        SDL_Texture* getSdlTexturePlayer();
        SDL_Texture* getSdlTextureLevels();
        SDL_Texture* getSdlTextureEnemies();
        SDL_Renderer* getRender();

        void displayMessage(int fontSize, SDL_Color color, SDL_Rect textureParams, std::string message);
        void cleanup();
};

#endif
