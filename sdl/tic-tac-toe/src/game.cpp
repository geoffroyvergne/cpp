#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

#include <game.hpp>
#include <plateau.hpp>
#include <piece.hpp>
#include <core.hpp>

Game::~Game() { 
    Core::getInstance()->cleanup();
}

void Game::renderView() {
    SDL_RenderClear(Core::getInstance()->getRender());

    plateau->display();
    plateau->displayPieces();
    currentPiece->display();
    
    std::string message = getScore() + " winner : " + getPlayer(lastWinner);

    Core::getInstance()->displayMessage(40, { 255, 165, 0 }, { 128, 20,  256, 35 }, Core::getInstance()->name);
    Core::getInstance()->displayMessage(20, { 128, 128, 128 }, { 120, 55,  260, 60 }, message);

    SDL_RenderPresent(Core::getInstance()->getRender());
}

void Game::startLoop() {
    
    int active = 1;
    SDL_Event e;
    while (active) { 
        // if winner is none, start a new game
        if(winner != none) {
            lastWinner = winner;
            // Increase score to the right player
            increaseScore(winner);
            SDL_Log("Game over Winner is %s score : %s", getPlayer(winner).c_str(), getScore().c_str());

            newGame();
            winner = none;
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
                        circleScore = 0;
                        crossScore = 0;
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
    this->plateau->casesUsed = 0;

    renderView();
}

void Game::increaseScore(Player player) {
    if(player == circle) {
        circleScore ++;
    } else if(player == cross) {
        crossScore ++;
    }
}

std::string Game::getScore() {
    return std::to_string(circleScore) + " / " + std::to_string(crossScore);
}

std::string Game::getPlayer(Player player) {
    if(player == circle) {
        return "circle";
    } else if(player == cross) {
        return "cross";
    }
    
    return "none";
}

void Game::togglePlayer() {
    if(currentPlayer == cross) currentPlayer = circle;
    else if(currentPlayer == circle) currentPlayer = cross;
}

void Game::validate() {
    // Check if there is a winner                        
    if(winner == none) {
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
