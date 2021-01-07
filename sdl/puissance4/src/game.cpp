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
        std::string message = this->name + " red : " + std::to_string(this->redScore) + " yellow : " + std::to_string(this->yellowScore);
        this->message->message = message;
        this->message->displayMessage();
        //message->displayMessage();
        plateau->display();
        currentPiece->display();
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
				SDL_Log("Quit\n");
                break;
			}

            // reset new game
            if (e.key.keysym.sym == SDLK_r) {
                newGame();
            }        

            renderView();

            switch( e.type ) {
                case SDL_KEYDOWN:

                    //SDL_Log("piece x %d piece y %d", currentPiece->textureParams.x, currentPiece->textureParams.y);
                    
                    if (e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_SPACE) {
                        //SDL_Log("SDLK_RETURN");
                        
                        validateRow();
                        renderView();

                        break;
                    }

                    // Right Arrow
                    if (e.key.keysym.sym == SDLK_RIGHT) {
                        //SDL_Log("SDLK_RIGHT");
                        currentPiece->moveRight();

                        break;
                    }

                    // Left Arrow
                    if (e.key.keysym.sym == SDLK_LEFT) {
                        //SDL_Log("SDLK_LEFT");
                        currentPiece->moveLeft();

                        break;
                    }

                    // Up Arrow
                    /*if (e.key.keysym.sym == SDLK_UP) {
                        //SDL_Log("SDLK_UP");
                        currentPiece->moveUp();

                        break;
                    }*/

                    // Down Arrow
                    /*if (e.key.keysym.sym == SDLK_DOWN) {
                        //SDL_Log("SDLK_DOWN");
                        currentPiece->moveDown();

                        break;
                    }*/
                break;
            }            
        }
        SDL_Delay(this->loopDelay);
    }
}

void Game::togglePlayer() {
    PieceType pieceType;
    if(currentPlayer == red) {
        currentPlayer = yellow;
        pieceType = yellow_circle;
    } else if(currentPlayer == yellow) {
        currentPlayer = red;
        pieceType = red_circle;       
    }

    this->currentPiece->togglePlayer(pieceType);
}

void Game::validateRow() {
    Player winner = plateau->lineDone();
    if(winner != player_none) {

        if(winner == yellow) yellowScore ++;
        if(winner == red) redScore ++;
        SDL_Delay(1000);
        newGame();
    } else {
        int rowFull = plateau->addNewPiece(currentPiece);
        if(!rowFull) togglePlayer();
    }
}

void Game::newGame() {
    for (auto piece : this->plateau->pieceList) {
        delete piece;
    } 
    this->plateau->pieceList.clear();
    this->plateau->casesUsed = 0;    
}

void Game::cleanup() {
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
	SDL_Quit();
}
