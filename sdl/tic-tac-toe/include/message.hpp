#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

#ifndef MESSAGE
#define MESSAGE

class Message {
    public:
        Message(SDL_Renderer *render);
        ~Message();
        std::string fontPath = "../assets/arial.ttf";
        SDL_Renderer *render;
        TTF_Font * font = NULL;
        int fontSize = 40;
        std::string message = "TIC TAC TOE";
        SDL_Color color = { 128, 128, 128 };
        SDL_Texture * sdlTexture = NULL;
        SDL_Surface * sdlSurface = NULL;
        SDL_Rect textureParams = { 128, 30,  256, 45 };

        void displayMessage();
        void cleanUp();

};

#endif