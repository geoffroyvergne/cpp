#include <iostream>
#include <SDL.h>

#include <game.hpp>
#include <player.hpp>

Game::Game() {
    /*std::string imagePath = "../assets/images-set.png";
    this->sdl_texture = IMG_LoadTexture(render, imagePath.c_str());*/
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
	window = SDL_CreateWindow(this->name.c_str(), 100, 100, this->width, this->height, SDL_WINDOW_SHOWN);
	if (window == NULL) {cleanup(); exit(EXIT_FAILURE);}

	// Create render
	render = SDL_CreateRenderer(window, -1, 0);
	//render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);	
	if (render == NULL) {cleanup(); exit(EXIT_FAILURE);}

    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    //SDL_RenderClear(render);
	//SDL_RenderPresent(render); 
}

void Game::renderView() {
    SDL_RenderClear(render);

    this->message->displayMessage();
    this->player1->piece->display();
    this->player2->piece->display();

    SDL_RenderPresent(render);
}

void Game::startLoop() {
    int active = 1;
    SDL_Event e;
    while (active) {
        
        while (SDL_PollEvent(&e)) {	            

            //if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE || e.key.keysym.sym == SDLK_q) {
            if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_q) {
				active = 0;
				SDL_Log("Quit");
			}            

            renderView();

            switch( e.type ) {
                case SDL_KEYDOWN:
                    if (e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_SPACE) {
                        if(this->player1->piece->pieceype == none) break;
                        
                        // Player 2 play random
                        this->player2->piece->randomPiece();
                        
                        // Update render
                        renderView();

                        SDL_Delay(1000);

                        this->result();
                        this->setWinner(winner);

                        SDL_Log("player1 : %s player2 : %s", this->player1->piece->name.c_str(), this->player2->piece->name.c_str());              
                        SDL_Log("partyNumber %d winner : %s", this->partyNumber, this->getWinner(winner)->name.c_str());                       
                        SDL_Log("%s" , getScore().c_str());

                        // Update score message
                        message->message = getScore();
                        
                        this->newGame();
                        
                        break;
                    }

                    if (e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_DOWN) {
                        //SDL_Log("change piece");

                        this->player1->piece->nextPiece();
                        
                        break;
                    }
                break;
            }
        }
        SDL_Delay(this->loopDelay); 
    }
}

void Game::result() {
    if(player1->piece->pieceype == none && player2->piece->pieceype == none) winner = playerNoneType;

    else if(player1->piece->pieceype == rock && player2->piece->pieceype == rock) winner = playerNoneType;
    else if(player1->piece->pieceype == rock && player2->piece->pieceype == paper) winner = player2Type;
    else if(player1->piece->pieceype == rock && player2->piece->pieceype == sissors) winner = player1Type;

    else if(player1->piece->pieceype == paper && player2->piece->pieceype == rock) winner = player1Type;
    else if(player1->piece->pieceype == paper && player2->piece->pieceype == paper) winner = playerNoneType;
    else if(player1->piece->pieceype == paper && player2->piece->pieceype == sissors) winner = player2Type;

    else if(player1->piece->pieceype == sissors && player2->piece->pieceype == rock) winner = player2Type;
    else if(player1->piece->pieceype == sissors && player2->piece->pieceype == paper) winner = player1Type;
    else if(player1->piece->pieceype == sissors && player2->piece->pieceype == sissors) winner = playerNoneType;

    else winner = playerNoneType;
}

void Game::setWinner(PlayerType type) {    
    if(type == player1Type) {
        player1->winner = 1;
        player1->score ++;
    }

    else if(type == player2Type) {
        player2->winner = 1;
        player2->score ++;
    }
}

Player* Game::getWinner(PlayerType type) {
    if(type == player1Type) return player1;
    if(type == player2Type) return player2;
    return playerNone;
}

std::string Game::getScore() {
    return "" + player1->name + " - " + std::to_string(player1->score) + " / " + player2->name + " - " + std::to_string(player2->score);
}

void Game::newGame() {
    partyNumber ++;
    this->player1->piece->togglePieceType(none);
    this->player1->winner = 0;

    this->player2->piece->togglePieceType(none);
    this->player2->winner = 0;

    winner = playerNoneType;
}

void Game::cleanup() {
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
	SDL_Quit();
}
