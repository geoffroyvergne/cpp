#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#ifndef SINGLETONINIT
#define SINGLETONINIT

class SingletonInit {
    private:
        std::string name = "shifumi";
        int width = 512;
        int height = 512;
        std::string imagePath = "../assets/images-set.png";
        std::string fontPath = "../assets/arial.ttf";

        static SingletonInit* instance;
        SingletonInit() {} //private constructor
        SingletonInit(const SingletonInit&) = delete; // copy constructor
        SingletonInit& operator=(const SingletonInit&) = delete; // assignment operator

        SDL_Window *window;
        SDL_Renderer *render;
        SDL_Texture *sdl_texture;

        TTF_Font * font;
        SDL_Texture * sdlTexture;
        SDL_Surface * sdlSurface;
        
    public:
        static SingletonInit* getInstance();
        void init();

        SDL_Window* getWindow();
        SDL_Texture* getSdlTexture();
        SDL_Renderer* getRender();

        void displayMessage(int fontSize, SDL_Color color, SDL_Rect textureParams, std::string message);

        void cleanup();
};

#endif
