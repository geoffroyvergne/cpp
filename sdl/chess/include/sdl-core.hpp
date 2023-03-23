#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#ifndef CORE
#define CORE

class SdlCore {
    private:
        static SdlCore* instance;
        SdlCore() {} //private constructor
        //Core();
        SdlCore(const SdlCore&) = delete; // copy constructor
        SdlCore& operator=(const SdlCore&) = delete; // assignment operator

        std::string imagePath = "../assets/symbols-v4.png";
        std::string fontPath = "../assets/arial.ttf";

        SDL_Window *window;
        SDL_Renderer *render;
        SDL_Texture *sdl_texture;

        TTF_Font * font;
        SDL_Texture * sdlTexture;
        SDL_Surface * sdlSurface;

    public:
        std::string name = "Chess";
        int width = 600;
        int height = 600;
        int loopDelay = 100;
        //int border = 50;
        int size=100;

        static SdlCore* getInstance();
        void init();

        SDL_Window* getWindow();
        SDL_Texture* getSdlTexture();
        SDL_Renderer* getRender();

        void displayMessage(int fontSize, SDL_Color color, SDL_Rect textureParams, std::string message);
        void cleanup();
};

#endif
