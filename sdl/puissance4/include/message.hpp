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
        TTF_Font * font;
        int fontSize = 40;
        std::string message = "puissance4";
        SDL_Color color = { 128, 128, 128 };
        SDL_Texture * sdlTexture;
        SDL_Surface * sdlSurface;
        SDL_Rect textureParams = { 128, 10,  256, 45 };

        void displayMessage();
        void cleanUp();

};

#endif
