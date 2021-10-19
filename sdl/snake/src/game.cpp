#include <iostream>
#include <SDL.h>
#include <game.hpp>

//Game::Game() {}

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

    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    SDL_RenderClear(render);
	SDL_RenderPresent(render); 
}

void Game::renderView() {
    SDL_RenderClear(render);
        plateau->display();
        //plateau->displayCurrentPiece();
        //plateau->displayPieces();
        plateau->snake->display();
    SDL_RenderPresent(render);
}

void Game::startLoop() {
    int active = 1;
    SDL_Event e;
    while (active) {
        while (SDL_PollEvent(&e)) {          
            //if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE || e.key.keysym.sym == SDLK_q) {
            if (e.type == SDL_QUIT) {
                active = 0;
                SDL_Log("Quit");
                break;
            }

            renderView();

            switch( e.type ) {
                case SDL_KEYDOWN:

                    if (e.key.keysym.sym == SDLK_UP) {
                        SDL_Log("SDLK_UP");                        
                        //break;
                        plateau->snake->moveUp();
                    }

                    if (e.key.keysym.sym == SDLK_DOWN) {
                        SDL_Log("SDLK_DOWN"); 
                        plateau->snake->moveDown();                       
                    }

                    if (e.key.keysym.sym == SDLK_LEFT) {
                        SDL_Log("SDLK_LEFT");      
                        plateau->snake->moveLeft();                  
                    }

                    if (e.key.keysym.sym == SDLK_RIGHT) {
                        SDL_Log("SDLK_RIGHT");     
                        plateau->snake->moveRight();                   
                    }

                    if (e.key.keysym.sym == SDLK_r) {
                        SDL_Log("SDLK_r");
                    }

                    break;
            }
        }
    }
}

void Game::cleanup() {
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
	SDL_Quit();
}
