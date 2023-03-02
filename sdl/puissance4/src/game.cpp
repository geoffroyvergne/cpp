#include <iostream>
#include <SDL.h>
#include <game.hpp>
#include <sdl-core.hpp>
#include <util.hpp>

Game::~Game() { 
    SdlCore::getInstance()->cleanup();
}

void Game::renderView() {
    SDL_RenderClear(SdlCore::getInstance()->getRender());

    plateau->display();
    plateau->displayPieces();
    currentPiece->display();
    
    std::string message = this->name + " red : " + std::to_string(this->redScore) + " yellow : " + std::to_string(this->yellowScore);

    SdlCore::getInstance()->displayMessage(40, { 255, 165, 0 }, { 128, 20,  256, 35 }, SdlCore::getInstance()->name);
    SdlCore::getInstance()->displayMessage(20, { 128, 128, 128 }, { 120, 55,  260, 60 }, message);

    SDL_RenderPresent(SdlCore::getInstance()->getRender());
}

void Game::startLoop() {
    int active = 1;
    SDL_Event e;
    while (active) {
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
            
            renderView();

            switch( e.type ) {
                case SDL_KEYDOWN:
                    
                    // Return
                    if (e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_SPACE) {                        
                        addPiece();                        
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
    if(currentPlayer == Player::red) {
        currentPlayer = Player::yellow;
        pieceType = PieceType::yellow_circle;
    } else if(currentPlayer == Player::yellow) {
        currentPlayer = Player::red;
        pieceType = PieceType::red_circle;       
    }

    this->currentPiece->togglePlayer(pieceType);
}

void Game::addPiece() {
    Piece* newPiece = plateau->addNewPiece(currentPiece);
    if(!newPiece->rowFull) {
        togglePlayer();
        winner = plateau->lineDone(newPiece);    
        validateRow();
    }
}

void Game::validateRow() {
    if(winner != Player::none) {
        if(winner == Player::yellow) yellowScore ++;
        if(winner == Player::red) redScore ++;
        plateau->resetContainers();

        renderView();
        SDL_Delay(100);
        newGame();
        
        SDL_Log("Winner is %s", Util::getPlayerString(currentPlayer).c_str());
    }
}

void Game::newGame() {
    this->plateau->clearPieceList();
    this->plateau->resetContainers();
    this->plateau->casesUsed = 0;  
    winner = Player::none;
}
