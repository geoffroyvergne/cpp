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
        int width = 500;
        int height = 500;
        int loopDelay = 1000;
        int cellSize  = 10;
        int nbCells = 5;
        int size = 50;

        static SdlCore* getInstance();
        void init();

        SDL_Window* getWindow();
        SDL_Renderer* getRender();

        void cleanup();
};

#endif
