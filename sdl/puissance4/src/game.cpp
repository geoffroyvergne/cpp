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

        //validateRow();  

        /*if(winner != player_none) {
            //lastWinner = winner;
            // Increase score to the right player
            //increaseScore(winner);
            //SDL_Log("Game over Winner is %s score : %s", getPlayer(winner).c_str(), getScore().c_str());

            newGame();
            winner = player_none;
            
            //SDL_Delay(1000);
            continue;            
        }*/

        while (SDL_PollEvent(&e)) {	            
            if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_q) {
				active = 0;
				SDL_Log("Quit\n");
                break;
			}

            // reset new game
            if (e.key.keysym.sym == SDLK_r) {
                newGame();
            }        

            //validateRow();  
            renderView();

            switch( e.type ) {
                case SDL_KEYDOWN:

                    //SDL_Log("piece x %d piece y %d", currentPiece->textureParams.x, currentPiece->textureParams.y);
                    
                    if (e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_SPACE) {                        
                        //renderView();
                        addPiece();
                        //validateRow();
                        break;
                    }

                    // Right Arrow
                    if (e.key.keysym.sym == SDLK_RIGHT) {
                        currentPiece->moveRight();

                        break;
                    }

                    // Left Arrow
                    if (e.key.keysym.sym == SDLK_LEFT) {
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

void Game::addPiece() {
    bool fullrow = plateau->addNewPiece(currentPiece);
    if(!fullrow) validateRow();

   //if(!rowFull) togglePlayer();
}

void Game::validateRow() {
    winner = plateau->lineDone(currentPlayer);

    if(winner != player_none) {
        if(winner == yellow) yellowScore ++;
        if(winner == red) redScore ++;

        renderView();
        SDL_Delay(1000);
        newGame();
        
        SDL_Log("Winner is %u", currentPlayer);
    } else {
        togglePlayer();
    }    
}

void Game::newGame() {
    this->plateau->pieceList.clear();
    this->plateau->casesUsed = 0;  
    winner = player_none;  
}
