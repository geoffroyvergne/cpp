#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

int main(int argc, char** argv) {

    // assets/sdl2-spritesheet-actual.png
    //std::string sprintAnimation = "../assets/sdl2-spritesheet-actual.png";
    std::string sprintAnimation = "../assets/capguy-walk.png";

    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    SDL_Window* window = SDL_CreateWindow("Animating using Sprite Sheets", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Texture* spriteSheet = NULL;
    SDL_Surface* temp = IMG_Load(sprintAnimation.c_str());
    spriteSheet = SDL_CreateTextureFromSurface(renderer, temp);
    SDL_FreeSurface(temp);

    SDL_Rect windowRect = {0, 0, 140, 200};

    SDL_Rect textureRect;
    textureRect.x = 0;
    textureRect.y = 0;

    SDL_QueryTexture(spriteSheet, NULL, NULL, &textureRect.w, &textureRect.h);
    
    textureRect.w /= 8;

    bool active = true;
    SDL_Event e;
    while (active) {       

        while (SDL_PollEvent(&e)) {	            
            if (e.type == SDL_QUIT) {
				active = false;
				SDL_Log("Quit\n");
			}        

            /*switch( e.type ) {
                case SDL_KEYDOWN:
                break;
            }*/           
        }

        int totalFrames = 8;
        int delayPerFrame = 100;
        int frame = (SDL_GetTicks() / delayPerFrame) % totalFrames;
        textureRect.x = frame * textureRect.w;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, spriteSheet, &textureRect, &windowRect);
        SDL_RenderPresent(renderer);
    }   

    SDL_DestroyTexture(spriteSheet);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit(); 

    return EXIT_SUCCESS;
}
