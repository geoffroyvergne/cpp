#include <iostream>
#include <SDL.h>

#include <game.hpp>
#include <player.hpp>

Game::Game() {
    
}

Game::~Game() { 
    Core::getInstance()->cleanup();
}

void Game::renderView() {
    SDL_RenderClear(Core::getInstance()->getRender());

    //SDL_Color color = { 128, 128, 128 };
    //SDL_Rect textureParams = { 128, 30,  256, 45 };

    Core::getInstance()->displayMessage(40, { 255, 165, 0 }, { 128, 20,  256, 35 }, Core::getInstance()->name);
    Core::getInstance()->displayMessage(20, { 128, 128, 128 }, { 120, 55,  260, 60 }, getScore());
    
    this->player1->piece->display();
    this->player2->piece->display();

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

                        SDL_Delay(this->loopDelay);

                        this->result();
                        this->setWinner(winner);

                        SDL_Log("player1 : %s player2 : %s", this->player1->piece->name.c_str(), this->player2->piece->name.c_str());              
                        SDL_Log("partyNumber %d winner : %s", this->partyNumber, this->getWinner(winner)->name.c_str());                       
                        SDL_Log("%s" , getScore().c_str());                    
                        
                        this->newGame();
                        
                        break;
                    }

                    if (e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_DOWN) {                       
                        this->player1->piece->nextPiece();
                        
                        break;
                    }

                    // reset key
                    if (e.key.keysym.sym == SDLK_r) {
                        SDL_Log("New Game\n");
                        partyNumber = 0;
                        player1->score = 0;
                        player2->score = 0;
                    }
                break;
            }
        }
        //SDL_Delay(this->loopDelay); 
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
    return "" + std::to_string(partyNumber) + " " + player1->name + " score " + std::to_string(player1->score) + " | " + player2->name + " score " + std::to_string(player2->score);
}

void Game::newGame() {
    partyNumber ++;
    this->player1->piece->togglePieceType(none);
    this->player1->winner = 0;

    this->player2->piece->togglePieceType(none);
    this->player2->winner = 0;

    winner = playerNoneType;
}
