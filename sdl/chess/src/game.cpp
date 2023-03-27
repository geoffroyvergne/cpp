#include <iostream>
#include <SDL.h>
#include <game.hpp>
#include <cursor.hpp>
#include <piece.hpp>
#include <square.hpp>
#include <sdl-core.hpp>

Game::Game() { 
    player1.id = 1;
    player1.name = "player1";
    player1.color = black;

    player2.id = 2;
    player2.name = "player2";
    player2.color = white;

    currentPlayer = player1;
}

Game::~Game() { 
   //Core::getInstance()->cleanup();
}

void Game::renderView() {
    SDL_RenderClear(SdlCore::getInstance()->getRender());
    this->board->displayBoard();
    this->board->display();
    this->cursor->display();

    SDL_SetRenderDrawColor(SdlCore::getInstance()->getRender(), 255, 255, 255, 255);
    SDL_RenderPresent(SdlCore::getInstance()->getRender());
    SDL_SetRenderDrawBlendMode(SdlCore::getInstance()->getRender(), SDL_BLENDMODE_BLEND);
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
        
        SDL_Delay(SdlCore::getInstance()->loopDelay);
    }
}

void Game::reset() {
    SDL_Log("New game");
    this->board->reset();
}

void Game::deletePiece() {
    selectPiece();
    if(this->cursor->currentPiece != NULL) {        
        this->board->deletePiece(&this->board->pieceList[this->cursor->origy][this->cursor->origx]);
        this->board->logBoard();
    }
    cancelSelectPiece();
}

void Game::selectPiece() {
    SDL_Log("Select");
    SDL_Log("Color : %d", this->cursor->color);
    SDL_Log("x %d y %d", cursor->x, cursor->y);
    if(this->cursor->currentPiece == NULL) {
        if(board->pieceList[cursor->y][cursor->x].type == none) return; 
        if(board->pieceList[cursor->y][cursor->x].color != this->cursor->color) {
            SDL_Log("Not your color");            
            return;
        }
        this->cursor->origx = cursor->x;
        this->cursor->origy = cursor->y;
        
        this->cursor->currentPiece = &board->pieceList[cursor->y][cursor->x];

        // TODO color possible positions
        this->board->showMove(board->pieceList[cursor->y][cursor->x].type, cursor->x, cursor->y);
    }
}

void Game::validatePiece() {
    SDL_Log("Validate");
    
    if(this->cursor->currentPiece == NULL) return;

    if(this->board->caseAlreadyUsed(this->cursor->currentPiece)) {
        SDL_Log("case already used");
        return;
    }

    // TODO validate move
    if(! this->board->validateMove(this->board->pieceList[cursor->y][cursor->x].type, this->cursor->x, this->cursor->y, this->cursor->origx, this->cursor->origy)) {
        SDL_Log("move not allowed");
        return;
    }

    // TODO delete challenger piece if any

    this->board->pieceList[cursor->y][cursor->x] = *this->cursor->currentPiece;
    this->board->pieceList[this->cursor->origy][this->cursor->origx] = *this->board->getNonePiece();
    this->cursor->currentPiece = NULL;

    this->togglePlayer();
    this->cursor->setColor();

    this->board->logBoard();
}

void Game::cancelSelectPiece() {
    SDL_Log("Cancel");
    this->board->pieceList[this->cursor->origy][this->cursor->origx] = *this->cursor->currentPiece;
    this->board->pieceList[this->cursor->origy][this->cursor->origx].x = this->cursor->origx;
    this->board->pieceList[this->cursor->origy][this->cursor->origx].y = this->cursor->origy;

    this->cursor->currentPiece = NULL;

    this->board->logBoard();
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

void Game::togglePlayer() {
    if(currentPlayer.id == 1) currentPlayer = player2;
    else currentPlayer = player1;

    cursor->color = currentPlayer.color;
    cursor->setColor();
}
