#include <iostream>
#include <SDL.h>
#include <game.hpp>
#include <cursor.hpp>
#include <piece.hpp>
#include <square.hpp>

Game::Game() { 
    //init();
    //this->sdl_texture_symbols = IMG_LoadTexture(render, "../assets/symbols-v4.png");
}

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
	window = SDL_CreateWindow(this->name.c_str(), 100, 100, this->width, this->width, SDL_WINDOW_SHOWN);
	if (window == NULL) {cleanup(); exit(EXIT_FAILURE);}

	// Create render
	//render = SDL_CreateRenderer(window, -1, 0);
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (render == NULL) {cleanup(); exit(EXIT_FAILURE);}

    //TTF_Init();

    SDL_SetRenderDrawColor(render, 4, 156, 216, 255);
}

void Game::renderView() {
    SDL_RenderClear(render);        
    this->plateau->display();
    this->cursor->display();
    SDL_RenderPresent(render);
}

void Game::startLoop() {
    int active = 1;
    SDL_Event e;
    const Uint8 *state = SDL_GetKeyboardState(NULL);

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
                    if (e.key.keysym.sym == SDLK_ESCAPE) {
                        SDL_Log("Escape");
                    }

                    if (e.key.keysym.sym == SDLK_RETURN) {
                        int cursorId = this->cursor->getId();                        
                        //Square *square = this->plateau->squareList.at(cursorId);

                        Square *square = this->plateau->getSquareById(cursorId);
                        Piece *piece = this->plateau->getPieceById(cursorId);
                        
                        //Piece *piece = this->plateau->pieceList.at(cursorId);
                        //Piece *piece = square->piece;

                        if(square != NULL) {
                            SDL_Log("Square : %s", square->colorStr.c_str());
                        }

                        if(piece != NULL) {
                            SDL_Log("Piece : %s %s", piece->name.c_str(), piece->colorStr.c_str());
                        }
                    }

                    if (e.key.keysym.sym == SDLK_UP) {                        
                        this->cursor->up();
                    }

                    if (e.key.keysym.sym == SDLK_DOWN) {                            
                        this->cursor->down();
                    }

                    if (e.key.keysym.sym == SDLK_LEFT) {                        
                        this->cursor->left();
                    }

                    if (e.key.keysym.sym == SDLK_RIGHT) {                        
                        this->cursor->right();
                    }
                    break;

                break;
            }
        }
        
        SDL_Delay(this->loopDelay);
    }
}

void Game::cleanup() {
    
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    //TTF_Quit();
    //SDL_DestroyTexture(sdl_texture_symbols);
	SDL_Quit();
}
