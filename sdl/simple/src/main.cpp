#include <iostream>
#include <SDL.h>

const int SCREEN_WIDTH  = 800;
const int SCREEN_HEIGHT = 600;

int main(int argc, char** argv) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        std::cerr << "Could not initialize SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* pWindow = NULL;
    pWindow = SDL_CreateWindow("Simple SDL Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if( pWindow ) {
        //SDL_Delay(3000);

        int active = 1;
        SDL_Event e;                      
        while (active) {            
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_q) {
                    active = 0;
                    SDL_Log("Quit");
                }                
            }
        }        
    }
    else {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    }

    SDL_Quit();

    return EXIT_SUCCESS;
}
