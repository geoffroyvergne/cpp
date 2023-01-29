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

        //std::string imagePath = "../assets/image-set.png";
        //SDL_Texture *sdl_texture_overworld = IMG_LoadTexture(render, "../assets/overworld-tileset.png");
        //SDL_Texture *sdl_texture_overworld_enemies = IMG_LoadTexture(render, "../assets/overworld-enemies.png");

        std::string imagePath_overworld = "../assets/overworld-tileset.png";
        std::string imagePath_overworld_enemies = "../assets/overworld-enemies.png";

        std::string imagePath_item = "../assets/items.png";
        std::string imagePath_link = "../assets/link.png";       
        
        SDL_Window *window;
        SDL_Renderer *render;
        //SDL_Texture *sdl_texture;
        SDL_Texture *sdl_texture_overworld;
        SDL_Texture *sdl_texture_overworld_enemies;

        SDL_Texture *sdl_texture_item;
        SDL_Texture *sdl_texture_link;

        TTF_Font * font;
        //SDL_Texture * sdlTexture;
        SDL_Surface * sdlSurface;

    public:
        std::string name = "Zelda";
        int height = 500;
        int width = 600;
        int loopDelay = 200;

        static Core* getInstance();
        void init();

        SDL_Window* getWindow();
        //SDL_Texture* getSdlTexture();
        SDL_Texture* getSdlTextureOverWorld();
        SDL_Texture* getSdlTextureOverworldEnemies();
        SDL_Texture* getSdlTextureItem();
        SDL_Texture* getSdlTextureLink();
        SDL_Renderer* getRender();

        void displayMessage(int fontSize, SDL_Color color, SDL_Rect textureParams, std::string message);
        void cleanup();
};

#endif
