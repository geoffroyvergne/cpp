#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

#include <game.hpp>
#include <plateau.hpp>
#include <piece.hpp>
#include <message.hpp>

void Game::init() {
    //SDL_Log("Init game");

    //First we need to start up SDL, and make sure it went ok
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
    
    //Message
    TTF_Init();    
}

void Game::startLoop() {
    Plateau *plateau = new Plateau(render);
    this->plateau = plateau;
    
    // Message
    message = new Message(render);

    // Init lastCurrentPiece
    currentPiece = new Piece(render, red_circle);
    currentPiece->textureParams.x = 210;
    currentPiece->textureParams.y = 210;

    currentPiece = plateau->addCurrentPiece(currentPiece, currentPlayer);
    
    int active = 1;
    SDL_Event e;
    while (active) { 
        // if winner is known, start a new game
        if(winner != none) {
            lastWinner = winner;
            // Increase score to the right player
            increaseScore(winner);
            SDL_Log("Winner is %s score : %s", getPlayer(winner).c_str(), getScore().c_str());

            newGame();
            winner = none;
            //SDL_Delay(1000);
            continue;            
        }

        // If all cases used Game over !
        if(this->plateau->casesUsed >= 9) {
            SDL_Log("Game Over null match");
            //SDL_Delay(1000);
            newGame();
            continue;
        } 
        
		while (SDL_PollEvent(&e)) {	
			if (e.type == SDL_QUIT) {
				active = 0;
				SDL_Log("Quit\n");
			}

            SDL_RenderClear(render);

            plateau->display();
            plateau->displayPieces();
            currentPiece->display();
           
            std::string message = "TIC TAC TOE " + getScore() + " winner : " + getPlayer(lastWinner);
            this->message->message = message;
            this->message->displayMessage();

            SDL_RenderPresent(render);

            switch( e.type ) {
                case SDL_KEYDOWN:
                    //Enter key
                    if (e.key.keysym.sym == SDLK_RETURN) {
                        //SDL_Log("SDLK_KP_ENTER\n");
                        
                        // Check if there is a winner                        
                        if(winner == none) {
                            // Check if case already ised
                            if(! plateau->caseAlreadyUsed(currentPiece)) {
                                winner = plateau->addNewPiece(currentPiece, currentPlayer);
                                togglePlayer();
                                currentPiece = plateau->addCurrentPiece(currentPiece, currentPlayer);  
                                this->plateau->casesUsed ++;                                                            
                            } else {                            
                                SDL_Log("Case already used");
                                //newGame();
                            }
                        }
                        
                        break;
                    }

                    // Up Arrow
                    if (e.key.keysym.sym == SDLK_UP) {
                        //SDL_Log("SDLK_UP\n");
                        currentPiece->moveUp();

                        break;
                    }

                    // Down Arrow
                    if (e.key.keysym.sym == SDLK_DOWN) {
                        //SDL_Log("SDLK_DOWN\n");
                        currentPiece->moveDown();

                        break;
                    }

                    // Right Arrow
                    if (e.key.keysym.sym == SDLK_RIGHT) {
                        //SDL_Log("SDLK_RIGHT\n");
                        currentPiece->moveRight();

                        break;
                    }

                    // Left Arrow
                    if (e.key.keysym.sym == SDLK_LEFT) {
                        //SDL_Log("SDLK_LEFT\n");
                        currentPiece->moveLeft();

                        break;
                    }

                break;
            }
		}
		SDL_Delay(this->loopDelay);        
	}

    delete(plateau);
}

void Game::newGame() {
    destroyTextures();
    
    for (auto piece : this->plateau->pieceList) {
        delete piece;
    } 
    this->plateau->pieceList.clear();

    this->plateau->casesUsed = 0;
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

void Game::destroyTextures() {

    for (size_t i = 0; i < this->plateau->pieceList.size(); ++i) {
		SDL_DestroyTexture(this->plateau->pieceList[i]->sdl_texture);
	}
}

void Game::cleanup() {
    TTF_Quit();
    //TTF_CloseFont(font);

    message->cleanUp();
    TTF_CloseFont(message->font);
    destroyTextures();    
	SDL_DestroyWindow(window);
	SDL_Quit();
}
