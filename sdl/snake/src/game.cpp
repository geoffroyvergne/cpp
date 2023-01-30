#include <iostream>
#include <SDL.h>
#include <game.hpp>
#include <direction.hpp>
#include <core.hpp>

//Game::Game() {}

Game::~Game() { 
    Core::getInstance()->cleanup();
}

void Game::renderView() {
    SDL_RenderClear(Core::getInstance()->getRender());
        plateau->display();
        //plateau->displayCurrentPiece();
        //plateau->displayPieces();
        plateau->snake->display();
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
                break;
            }

            //renderView();

            switch( e.type ) {
                case SDL_KEYDOWN:

                    if (e.key.keysym.sym == SDLK_UP) {
                        //SDL_Log("SDLK_UP");
                        plateau->snake->changeDirection(up);
                    }

                    if (e.key.keysym.sym == SDLK_DOWN) {
                        //SDL_Log("SDLK_DOWN");
                        plateau->snake->changeDirection(down);                     
                    }

                    if (e.key.keysym.sym == SDLK_LEFT) {
                        //SDL_Log("SDLK_LEFT");
                        plateau->snake->changeDirection(left);                
                    }

                    if (e.key.keysym.sym == SDLK_RIGHT) {
                        //SDL_Log("SDLK_RIGHT");
                        plateau->snake->changeDirection(right);                 
                    }

                    if (e.key.keysym.sym == SDLK_r) {
                        SDL_Log("SDLK_r");
                    }

                    break;
            }
        }
        SDL_Delay(Core::getInstance()->loopDelay);
        plateau->snake->moveCurrentDirection();
        renderView();
    }
    
}
