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
        plateau->displayCurrentPiece();
        plateau->displayPieces();
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

                    //SDL_Log("piece x %d piece y %d", currentPiece->textureParams.x, currentPiece->textureParams.y);
                    //SDL_Log("piece position x %d position y %d", plateau->currentPiece->positionX, plateau->currentPiece->positionY);
                    
                    if (e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_SPACE) {
                        //SDL_Log("SDLK_RETURN");

                        plateau->addCurrentPiece();
                        renderView();

                        break;
                    }

                    if (e.key.keysym.sym == SDLK_r) {
                        //SDL_Log("SDLK_r");
                        plateau->rotateCurrentPiece();
                    }

                    // Right Arrow
                    if (e.key.keysym.sym == SDLK_RIGHT) {
                        //SDL_Log("SDLK_RIGHT");
                        plateau->currentPiece->moveRight();

                        break;
                    }

                    // Left Arrow
                    if (e.key.keysym.sym == SDLK_LEFT) {
                        //SDL_Log("SDLK_LEFT");
                        plateau->currentPiece->moveLeft();

                        break;
                    }

                    // Up Arrow
                    if (e.key.keysym.sym == SDLK_UP) {
                        //SDL_Log("SDLK_UP\n");
                        plateau->currentPiece->moveUp();

                        break;
                    }

                    // Down Arrow
                    if (e.key.keysym.sym == SDLK_DOWN) {
                        //SDL_Log("SDLK_DOWN\n");
                        plateau->currentPiece->moveDown();

                        break;
                    }

                    break;
            }            
        }
        SDL_Delay(this->loopDelay);
    }
}

void Game::cleanup() {
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
	SDL_Quit();
}
