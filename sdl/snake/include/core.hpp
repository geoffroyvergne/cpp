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

        std::string imagePath = "../assets/image-set.png";
        std::string fontPath = "../assets/arial.ttf";

        SDL_Window *window;
        SDL_Renderer *render;
        SDL_Texture *sdl_texture;

        TTF_Font * font;
        SDL_Texture * sdlTexture;
        SDL_Surface * sdlSurface;

    public:
        std::string name = "Snake";
        int width = 550;
        int height = 800;
        int loopDelay = 500;

        static Core* getInstance();
        void init();

        SDL_Window* getWindow();
        SDL_Texture* getSdlTexture();
        SDL_Renderer* getRender();

        void displayMessage(int fontSize, SDL_Color color, SDL_Rect textureParams, std::string message);
        void cleanup();
};

#endif
