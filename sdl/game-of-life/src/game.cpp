#include <iostream>
#include <SDL.h>
#include <sdl-core.hpp>
#include <game.hpp>

Game::~Game() { 
    SdlCore::getInstance()->cleanup();
}

void Game::renderView() {
    SDL_RenderClear(SdlCore::getInstance()->getRender());

    board->displayCells();
    board->display();
    board->cellsEnvironment();

    SDL_SetRenderDrawColor(SdlCore::getInstance()->getRender(), 255, 255, 255, 255);
    SDL_RenderPresent(SdlCore::getInstance()->getRender());
}

void Game::startLoop() {
    int iterations = 0;
    int active = 1;
    SDL_Event e;
    while (active) {

        renderView();

        SDL_Delay(SdlCore::getInstance()->loopDelay);       
        iterations++;
        if(iterations == 10) active = 0;

        while (SDL_PollEvent(&e)) {	            
            if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_q) {
				active = 0;
				SDL_Log("Quit");
                break;
			}

            // reset new game
            if (e.key.keysym.sym == SDLK_r) {
                newGame();
            }

            // pause game
            if (e.key.keysym.sym == SDLK_p) {
                SDL_Log("Pause");
                if(pause) pause = false;
                else pause = true;
            }

            /*switch( e.type ) {
                case SDL_KEYDOWN:
                break;
            }*/           
        }
        
    }
}

void Game::newGame() {
    SDL_Log("New Game");
    //board->updateCellTable();
    //plateau->fillTable();
}
