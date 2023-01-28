#include <iostream>
#include <SDL.h>
#include <game.hpp>
#include <core.hpp>

Game::~Game() { 
    Core::getInstance()->cleanup();
}

void Game::renderView() {
    SDL_RenderClear(Core::getInstance()->getRender());

    plateau->display();
    plateau->displayPieces();
    currentPiece->display();
    
    std::string message = this->name + " red : " + std::to_string(this->redScore) + " yellow : " + std::to_string(this->yellowScore);

    Core::getInstance()->displayMessage(40, { 255, 165, 0 }, { 128, 20,  256, 35 }, Core::getInstance()->name);
    Core::getInstance()->displayMessage(20, { 128, 128, 128 }, { 120, 55,  260, 60 }, message);

    SDL_RenderPresent(Core::getInstance()->getRender());
}

void Game::startLoop() {
    int active = 1;
    SDL_Event e;
    while (active) {        
        while (SDL_PollEvent(&e)) {	            
            //if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE || e.key.keysym.sym == SDLK_q) {
            if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_q) {
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
