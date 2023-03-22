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
        SdlCore(const SdlCore&) = delete; // copy constructor
        SdlCore& operator=(const SdlCore&) = delete; // assignment operator

        SDL_Window *window;
        SDL_Renderer *render;

    public:
        std::string name = "Game of life";
        //int width = 800;
        //int height = 600;

        int loopDelay = 100;        
        int size = 10;

        static SdlCore* getInstance();
        void init(int width, int height);

        SDL_Window* getWindow();
        SDL_Renderer* getRender();

        void cleanup();
};

#endif
