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
                        this->cancelSelectPiece();                        
                    }

                    /*if (e.key.keysym.sym == SDLK_m) {
                        this->replacePiece();                        
                    }*/

                    if (e.key.keysym.sym == SDLK_RETURN) {  
                        this->selectPiece();                                           
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

void Game::selectPiece() {
    int cursorId = this->cursor->getId();                                                
    Square *currentSquarePtr = this->plateau->getSquareById(cursorId);

    if(currentSquarePtr->piece != NULL) {
        SDL_Log("Selected piece : %s, %s", currentSquarePtr->piece->name.c_str(), currentSquarePtr->piece->colorStr.c_str());
    }

    /*if(currentSquarePtr->piece != NULL) {
        Square currentSquare = *currentSquarePtr;
        this->cursor->sourceSquare = &currentSquare;
        this->cursor->sourceSquareId = cursorId;
        currentSquarePtr->piece = NULL;

        SDL_Log("Selected piece : %s, %s", this->cursor->sourceSquare->piece->name.c_str(), this->cursor->sourceSquare->piece->colorStr.c_str());
    }*/
}

/*void Game::replacePiece() {
    int cursorId = this->cursor->getId();                                                
    Square *currentSquare = this->plateau->getSquareById(cursorId);
    currentSquare->piece = this->cursor->sourceSquare->piece;

    SDL_Log("Moved piece : %s, %s", this->cursor->sourceSquare->piece->name.c_str(), this->cursor->sourceSquare->piece->colorStr.c_str());
}*/

void Game::cancelSelectPiece() {
    //if(this->cursor->sourceSquare != NULL) {
        //int sourceSquareId = this->cursor->sourceSquareId;
        //Square *sourceSquare = this->plateau->getSquareById(this->cursor->sourceSquareId);
        //sourceSquare->piece = this->cursor->sourceSquare->piece;

        //SDL_Log("Replaced piece : %s, %s", this->cursor->sourceSquare->piece->name.c_str(), this->cursor->sourceSquare->piece->colorStr.c_str());
        //this->cursor->sourceSquare = NULL;
        //this->cursor->sourceSquareId = 0;
    //}
}

void Game::cleanup() {
    
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    //TTF_Quit();
    //SDL_DestroyTexture(sdl_texture_symbols);
	SDL_Quit();
}
