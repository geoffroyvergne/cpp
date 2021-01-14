#include <iostream>
#include <SDL.h>
#include <game.hpp>
#include <message.hpp>

Game::~Game() { 
    cleanup();
}

void Game::init() {
    //Start up SDL, and make sure it went ok
	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not initialize SDL: %s\n", SDL_GetError());
        
		exit(EXIT_FAILURE);
	}

	// Create window
	window = SDL_CreateWindow(this->name.c_str(), 100, 100, this->width, this->height, SDL_WINDOW_SHOWN);
	if (window == NULL) {cleanup(); exit(EXIT_FAILURE);}

	// Create render
	render = SDL_CreateRenderer(window, -1, 0);
	//render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (render == NULL) {cleanup(); exit(EXIT_FAILURE);}

    TTF_Init();
}

void Game::renderView() {
    SDL_RenderClear(render);        
        displayIntro();
        displayGame();
    SDL_RenderPresent(render);
}

void Game::displayIntro() {
    if(SDL_GetTicks() < 3000) {
        if(intro != NULL) {
            SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
            
            intro->textureParams = { 128, 128,  256, 45 };
            intro->message = "Nintendo";
        }
        intro->displayMessage();
    }
}

void Game::displayGame() {
    if(SDL_GetTicks() > 3000) {        
        SDL_SetRenderDrawColor(render, 4, 156, 216, 255);
    }
}

void Game::startLoop() {
    renderView();
    int active = 1;
    SDL_Event e;
    while (active) {
        if(SDL_GetTicks() < 10000) renderView();
        while (SDL_PollEvent(&e)) {          
            if (e.type == SDL_QUIT) {
                active = 0;
                SDL_Log("Quit");
                break;
            }

            renderView();

            switch( e.type ) {
                case SDL_KEYDOWN:
                    if (e.key.keysym.sym == SDLK_RETURN) {
                        SDL_Log("SDLK_RETURN");
                    }
            }
        
        }
        SDL_Delay(this->loopDelay);
    }
}

void Game::cleanup() {
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    TTF_Quit();
	SDL_Quit();
}
