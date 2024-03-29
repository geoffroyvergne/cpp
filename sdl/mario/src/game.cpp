#include <iostream>
#include <SDL.h>
#include <game.hpp>
#include <message.hpp>
#include <player.hpp>
#include <core.hpp>

Game::Game() { 
    
}

Game::~Game() { 
    Core::getInstance()->cleanup();
}

void Game::renderView() {
    SDL_RenderClear(Core::getInstance()->getRender());        
        //displayIntro();
        displayGame();
        this->player->display();
    SDL_RenderPresent(Core::getInstance()->getRender());
}

/*void Game::displayIntro() {
    if(SDL_GetTicks() < 3000) {
        if(intro != NULL) {
            SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
            
            intro->textureParams = { 128, 128,  256, 45 };
            intro->message = "Nintendo";
        }
        intro->displayMessage();
    }
}*/

void Game::displayGame() {
    //if(SDL_GetTicks() > 3000) {        
        SDL_SetRenderDrawColor(Core::getInstance()->getRender(), 4, 156, 216, 255);
        
        this->currentLevel->display();
    //}
}

void Game::newLevel(World world) {
    if(this->currentLevel != nullptr) delete this->currentLevel;
    currentLevel = new Level(world);
}

void Game::startLoop() {
    renderView();
    int active = 1;
    SDL_Event e;
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    while (active) {
        this->fall(state);

        while (SDL_PollEvent(&e)) {      
            if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_q) {
                active = 0;
                SDL_Log("Quit");
                break;
            }

            //renderView();

            switch( e.type ) {                     
                case SDL_KEYDOWN:
                    if (e.key.keysym.sym == SDLK_RETURN) {
                        SDL_Log("SDLK_RETURN");
                    }   
            }
        }

        if (state[SDL_SCANCODE_R]) {
            this->moveRight(state);
        }

        if (state[SDL_SCANCODE_L]) {
            this->moveLeft(state);
        }

        if (state[SDL_SCANCODE_U]) {            
            this->moveUp(state);
        }

        if (state[SDL_SCANCODE_D]) {
            this->moveDown(state);
        }

        if (state[SDL_SCANCODE_RIGHT]) {
            this->walkRight(state);
        }

        if (state[SDL_SCANCODE_LEFT]) {
            this->walkLeft(state);
        }

        if (state[SDL_SCANCODE_UP]) {
            this->jump(state);
        }

        /*if (state[SDL_SCANCODE_DOWN]) {
            this->fall(state);
        }*/
        
        SDL_Delay(this->loopDelay);
    }
}

void Game::moveLeft(const Uint8 *state) {
    player->moveLeft();
    currentLevel->moveLeft();
    //renderView();
}

void Game:: moveRight(const Uint8 *state) {
    player->moveRight();
    currentLevel->moveRight();
    //renderView();
}

void Game::moveDown(const Uint8 *state) {  
    player->moveDown(30);
    //renderView();
    //SDL_Delay(25);
}

void Game::moveUp(const Uint8 *state) {  
    player->moveUp(30);
    //renderView();
    //SDL_Delay(25);
}

void Game::walkLeft(const Uint8 *state) {
    if(player->playerDirection != PlayerDirection::left || !currentLevel->detectCollision(this->player)) {
        currentLevel->moveLeft();
        player->walkLeft();
        
        renderView();
    }
}

void Game::walkRight(const Uint8 *state) {
    if(player->playerDirection != PlayerDirection::right || !currentLevel->detectCollision(this->player)) {
        currentLevel->moveRight();
        player->walkRight();
        
        renderView();
    }
}

void Game::jump(const Uint8 *state) {
    for(int i=0; i<8; i++) {    
        
        if(!currentLevel->detectCollision(this->player)) {
            this->moveUp(state);
            if(currentLevel->detectCollision(this->player)) {
                this->moveDown(state);
                break;
            } 
            this->moveDown(state);
        }

        if (state[SDL_SCANCODE_RIGHT]) {
            this->walkRight(state);
        }

        if (state[SDL_SCANCODE_LEFT]) {
            this->walkLeft(state);
        }
        
        player->jump(30);
        renderView();
        SDL_Delay(25);
    }
}

void Game::fall(const Uint8 *state) {    
    while(true) {
        if(this->player->destTextureParams.y > this->height) break;

        if(!currentLevel->detectCollision(this->player)) {
            this->moveDown(state);
            if(currentLevel->detectCollision(this->player)) {
                this->moveUp(state);
                break;
            } else {
                this->moveUp(state);
            }
        } else break;

        if (state[SDL_SCANCODE_RIGHT]) {
            this->walkRight(state);
        }

        if (state[SDL_SCANCODE_LEFT]) {
            this->walkLeft(state);
        }
        
        player->fall(30);
        renderView();
        SDL_Delay(25);
    }
}

/*void Game::cleanup() {
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    TTF_Quit();
	SDL_Quit();
}*/
