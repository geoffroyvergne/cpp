#include <iostream>
#include <SDL.h>
#include <game.hpp>
#include <plateau.hpp>
#include <piece.hpp>

void Game::init() {
    SDL_Log("Init game");

    //First we need to start up SDL, and make sure it went ok
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

/*void Game::loadPlateau() {
    Plateau *plateau = new Plateau(render);
    plateau->display();
}*/

void Game::startLoop() {
    Plateau *plateau = new Plateau(render);

    // + 180
    Piece *circlePiece1 = new Piece(render, circle);
    circlePiece1->textureParams.x = 30;
    circlePiece1->textureParams.y = 30;

    Piece *crossPiece1 = new Piece(render, cross);
    crossPiece1->textureParams.x = 210;
    crossPiece1->textureParams.y = 30;

    Piece *circlePiece2 = new Piece(render, circle);
    circlePiece2->textureParams.x = 390;
    circlePiece2->textureParams.y = 30;

    Piece *crossPiece2 = new Piece(render, cross);
    crossPiece2->textureParams.x = 30;
    crossPiece2->textureParams.y = 210;
    
    int active = 1;
    SDL_Event e;
    while (active) {
		while (SDL_PollEvent(&e)) {	
			if (e.type == SDL_QUIT) {
				active = 0;
				SDL_Log("Quit\n");
			}

            SDL_RenderClear(render);

            plateau->display();
            circlePiece1->display();
            crossPiece1->display();
            circlePiece2->display();
            crossPiece2->display();

            SDL_RenderPresent(render);

            switch( e.type ) {
                case SDL_KEYDOWN:
                    // Up Arrow
                    if (e.key.keysym.sym == SDLK_UP) {
                        SDL_Log("SDLK_UP\n");

                        break;
                    }

                break;
            }
		}
		SDL_Delay(this->loopDelay);

        
	}
}

void Game::cleanup() {
	SDL_DestroyWindow(window);
	SDL_Quit();
}
