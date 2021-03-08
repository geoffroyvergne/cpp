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

void Game::reset() {
    SDL_Log("New game");
    this->plateau->reset();
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
    //const Uint8 *state = SDL_GetKeyboardState(NULL);

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

                    if (e.key.keysym.sym == SDLK_r) {
                        this->reset();
                    }

                    if (e.key.keysym.sym == SDLK_d) {
                        this->deletePiece();
                    }

                    if (e.key.keysym.sym == SDLK_v) {
                        this->validatePiece();                        
                    }

                    if (e.key.keysym.sym == SDLK_s) {  
                        this->selectPiece();                                           
                    }

                    if (e.key.keysym.sym == SDLK_UP) {                        
                        this->cursorUp();
                    }

                    if (e.key.keysym.sym == SDLK_DOWN) {                            
                        this->cursorDown();
                    }

                    if (e.key.keysym.sym == SDLK_LEFT) {                        
                        this->cursorLeft();
                    }

                    if (e.key.keysym.sym == SDLK_RIGHT) {                        
                        this->cursorRight();
                    }
                    break;

                break;
            }
        }
        
        SDL_Delay(this->loopDelay);
    }
}

void Game::deletePiece() {
    if(this->cursor->currentPiece == NULL) {
        int cursorId = this->cursor->getId();
        Piece *piece = this->plateau->getPieceById(cursorId);

        this->plateau->deletePieceById(cursorId);
        //SDL_Log("Deleted piece id : %d %s %s", piece->id, piece->name.c_str(), piece->colorStr.c_str());
    }
}

void Game::selectPiece() {
    if(this->cursor->currentPiece == NULL) {
        int cursorId = this->cursor->getId();
        Piece *piece = this->plateau->getPieceById(cursorId);

        if(piece != NULL) {
            //SDL_Log("Selected piece id : %d %s %s", piece->id, piece->name.c_str(), piece->colorStr.c_str());
            this->cursor->currentPiece = piece;
        }
    }
}

void Game::validatePiece() {
    if(this->cursor->currentPiece != NULL) {
        int currentId = this->cursor->currentPiece->id;
        Piece *currentPiece = this->plateau->getPieceById(currentId);

        int newId = this->cursor->currentPiece->calculateNewId();

        if(this->cursor->currentPiece->validateMove(currentId, newId)) {
            if(this->plateau->caseAlreadyUsed(this->cursor->getId())) {
                Piece *deletedPiece = this->plateau->getPieceById(newId);
                
                this->plateau->deletePieceById(this->cursor->getId());
                //SDL_Log("Deleted piece id : %d %s %s", deletedPiece->id, deletedPiece->name.c_str(), deletedPiece->colorStr.c_str());
                SDL_Log("%s %s take %s %s in %s", 
                    this->cursor->currentPiece->name.c_str(), 
                    this->cursor->currentPiece->colorStr.c_str(),
                    deletedPiece->name.c_str(), 
                    deletedPiece->colorStr.c_str(),
                    this->plateau->getSquarePositionById(deletedPiece->id).c_str()
                );
            }

            //SDL_Log("Validated selected piece from id : %d to id %d %s %s", currentId, newId, this->cursor->currentPiece->name.c_str(), this->cursor->currentPiece->colorStr.c_str());
            
            this->cursor->currentPiece->setId(newId);
            this->cursor->currentPiece = NULL;
        }
    }
}

void Game::cancelSelectPiece() {
    if(this->cursor->currentPiece != NULL) {
        this->cursor->currentPiece->setDestTextureParam(this->cursor->currentPiece->id);

        SDL_Log("Cancel selected piece id %d %s %s", this->cursor->currentPiece->id, this->cursor->currentPiece->name.c_str(), this->cursor->currentPiece->colorStr.c_str());
        
        this->cursor->currentPiece = NULL;
    }
}

void Game::cursorUp() {
    this->cursor->up();

    if(this->cursor->currentPiece != NULL) {
        this->cursor->currentPiece->up();
    }
}

void Game::cursorDown() {
    this->cursor->down();

    if(this->cursor->currentPiece != NULL) {
        this->cursor->currentPiece->down();
    }
}

void Game::cursorLeft() {
    this->cursor->left();

    if(this->cursor->currentPiece != NULL) {
        this->cursor->currentPiece->left();
    }
}

void Game::cursorRight() {
    this->cursor->right();

    if(this->cursor->currentPiece != NULL) {
        this->cursor->currentPiece->right();
    }
}

void Game::cleanup() {
    
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    //TTF_Quit();
    SDL_DestroyTexture(sdl_texture_symbols);
	SDL_Quit();
}
