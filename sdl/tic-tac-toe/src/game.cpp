#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

#include <game.hpp>
#include <plateau.hpp>
#include <piece.hpp>
#include <sdl-core.hpp>

Game::~Game() { 
    SdlCore::getInstance()->cleanup();
}

void Game::renderView() {
    SDL_RenderClear(SdlCore::getInstance()->getRender());

    plateau->display();
    plateau->displayPieces();
    currentPiece->display();
    
    std::string message = getScore() + " winner : " + getPlayer(lastWinner);

    SdlCore::getInstance()->displayMessage(40, { 255, 165, 0 }, { 128, 20,  256, 35 }, SdlCore::getInstance()->name);
    SdlCore::getInstance()->displayMessage(20, { 128, 128, 128 }, { 120, 55,  260, 60 }, message);

    SDL_SetRenderDrawColor(SdlCore::getInstance()->getRender(), 255, 255, 255, 255);
    SDL_RenderPresent(SdlCore::getInstance()->getRender());
}

void Game::startLoop() {
    
    int active = 1;
    SDL_Event e;

    renderView();

    while (active) { 
        // if winner is none, start a new game
        if(winner != Player::none) {
            lastWinner = winner;
            // Increase score to the right player
            increaseScore(winner);
            SDL_Log("Game over Winner is %s score : %s", getPlayer(winner).c_str(), getScore().c_str());

            newGame();
            winner = Player::none;
            //SDL_Delay(1000);
            continue;            
        }

        // If all cases used Game over !
        if(this->plateau->casesUsed >= 9) {
            SDL_Log("Game Over no winner");
            //SDL_Delay(1000);
            newGame();
            continue;
        } 
        
		while (SDL_PollEvent(&e)) {	
            if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_q) {
				active = 0;
				SDL_Log("Quit\n");
			}

            renderView();

            switch( e.type ) {
                case SDL_KEYDOWN:                    
                    //Enter key
                    if (e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_SPACE) {
                        validate();
                        
                        break;
                    }

                    // reset key
                    if (e.key.keysym.sym == SDLK_r) {
                        SDL_Log("New Game\n");
                        
                        newGame();
                    }

                    // Up Arrow
                    if (e.key.keysym.sym == SDLK_UP) {
                        currentPiece->moveUp();

                        break;
                    }

                    // Down Arrow
                    if (e.key.keysym.sym == SDLK_DOWN) {
                        currentPiece->moveDown();

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

    delete(plateau);
    delete(currentPiece);
}

void Game::newGame() {    
    this->plateau->clearPieceList();
    this->plateau->resetContainers();
    this->plateau->casesUsed = 0;

    circleScore = 0;
    crossScore = 0;
}

void Game::increaseScore(Player player) {
    if(player == Player::circle) {
        circleScore ++;
    } else if(player == Player::cross) {
        crossScore ++;
    }
}

std::string Game::getScore() {
    return std::to_string(circleScore) + " / " + std::to_string(crossScore);
}

std::string Game::getPlayer(Player player) {
    if(player == Player::circle) {
        return "circle";
    } else if(player == Player::cross) {
        return "cross";
    }
    
    return "none";
}

void Game::togglePlayer() {
    if(currentPlayer == Player::cross) currentPlayer = Player::circle;
    else if(currentPlayer == Player::circle) currentPlayer = Player::cross;
}

void Game::validate() {
    // Check if there is a winner                        
    if(winner == Player::none) {
        // Check if case already ised
        if(! plateau->caseAlreadyUsed(currentPiece)) {
            winner = plateau->addNewPiece(currentPiece, currentPlayer);
            this->plateau->displayTable();
            togglePlayer();
            currentPiece = plateau->addCurrentPiece(currentPiece, currentPlayer);  
            this->plateau->casesUsed ++;
        } else {                            
            SDL_Log("Case already used");
        }
    }
}

void Game::destroyTextures() {
    /*for (size_t i = 0; i < this->plateau->pieceList.size(); ++i) {
		//SDL_DestroyTexture(this->plateau->pieceList[i]->sdl_texture);
	}*/
}
