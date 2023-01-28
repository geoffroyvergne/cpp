#include <iostream>
#include <SDL.h>
#include <game.hpp>
#include <core.hpp>

//Game::Game() {}

Game::~Game() { 
     Core::getInstance()->cleanup();
}

void Game::renderView() {
    SDL_RenderClear(Core::getInstance()->getRender());
    plateau->display();
    plateau->displayCurrentPiece();
    //plateau->displayPieces();
    SDL_RenderPresent(Core::getInstance()->getRender());
}

void Game::startLoop() {

    int active = 1;
    SDL_Event e;
    while (active) {
        while (SDL_PollEvent(&e)) {          
            if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_q) {
                active = 0;
                SDL_Log("Quit");
                break;
            }

            renderView();

            switch( e.type ) {
                case SDL_KEYDOWN:
                    
                    //SDL_Log("piece x %d piece y %d", currentPiece->textureParams.x, currentPiece->textureParams.y);
                    //SDL_Log("piece position x %d position y %d", plateau->currentPiece->positionX, plateau->currentPiece->positionY);

                    if (e.key.keysym.sym == SDLK_RETURN) {
                        //SDL_Log("SDLK_RETURN");

                        plateau->addCurrentPiece();
                        renderView();

                        //break;
                    }

                    if (e.key.keysym.sym == SDLK_p) {
                        if(pause) pause = 0;
                        else pause = 1;
                    }

                    if (e.key.keysym.sym == SDLK_c) {
                        plateau->resetWall();
                    }

                    if (e.key.keysym.sym == SDLK_r) {
                        //SDL_Log("SDLK_r");
                        plateau->rotateCurrentPiece();
                        if(plateau->detectCollision()) {
                            plateau->rotateCurrentPieceToPreviousPosition();
                        }
                        //break;
                    }

                    // Right Arrow
                    if (e.key.keysym.sym == SDLK_RIGHT) {
                        //SDL_Log("SDLK_RIGHT");
                        plateau->currentPiece->moveRight();
                        if(plateau->detectCollision()) {
                            plateau->currentPiece->moveLeft();
                        }
                        //break;
                    }

                    // Left Arrow
                    if (e.key.keysym.sym == SDLK_LEFT) {
                        //SDL_Log("SDLK_LEFT");
                        plateau->currentPiece->moveLeft();
                        if(plateau->detectCollision()) {
                            plateau->currentPiece->moveRight();
                        }

                        //break;
                    }

                    // Up Arrow
                    if (e.key.keysym.sym == SDLK_UP) {
                        //SDL_Log("SDLK_UP");
                        plateau->currentPiece->moveUp();

                        //break;
                    }

                    // Down Arrow
                    if (e.key.keysym.sym == SDLK_DOWN) {
                        //SDL_Log("SDLK_DOWN");
                        this->moveDown();
                        //break;
                    }
                    
                    //this->plateau->detectCollision();
                    break;
                    
            }
        
        }
        SDL_Delay(Core::getInstance()->loopDelay);        

        // Automate piece move down
        if(iterations % this->speed == 0 && !pause) {
            this->moveDown(); 
            renderView();           
        }
        iterations++;
    }
}

void Game::moveDown() {
    plateau->currentPiece->moveDown();
    if(plateau->detectCollision()) {
        plateau->currentPiece->moveUp();
        //SDL_Log("Reached bottom");
        
        for (size_t i = 0; i < this->plateau->currentPiece->blockList.size(); ++i) {
            this->plateau->wallList.push_back(this->plateau->currentPiece->blockList[i]);            
        }

        int lineDone = 0;
        while((lineDone = plateau->detectLineDone()) > 0) {
            SDL_Log("Line Done");
            plateau->removeLine(lineDone);
            plateau->moveDownLine(lineDone);
        }

        plateau->addCurrentPiece();        

        if(plateau->gameOver()) {
            plateau->resetWall();
            plateau->resetWall();
        }

        //renderView();
    }
}
