#include <iostream>
#include <SDL.h>
#include <game.hpp>
#include <sprite.hpp>
#include <sprite-type.hpp>
#include <levels.hpp>
#include <enemy.hpp>
#include <enemy-type.hpp>
#include <core.hpp>

Game::~Game() { 
    Core::getInstance()->cleanup();
}

void Game::renderView() {
    SDL_RenderClear(Core::getInstance()->getRender());        
        this->currentLevel->display();
        this->player->display();
    SDL_RenderPresent(Core::getInstance()->getRender());
}

void Game::addLevel(Worlds level) {
    if(currentLevel != NULL) delete currentLevel;    
    currentLevel = new Level(level);

    SDL_Log("Level number : %s", currentLevel->name.c_str());
}

void Game::startLoop() {
    int active = 1;
    SDL_Event e;
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    while (active) {
        while (SDL_PollEvent(&e)) {          
            if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_q) {
                active = 0;
                SDL_Log("Quit");
                break;
            }

            renderView();
        }

        if (state[SDL_SCANCODE_RETURN]) {
            this->attack();
        }
    
        if (state[SDL_SCANCODE_RIGHT]) {
            this->right();
        }

        if (state[SDL_SCANCODE_LEFT]) {
            this->left();
        }

        if (state[SDL_SCANCODE_UP]) {
            this->up();            
        }

        if (state[SDL_SCANCODE_DOWN]) {
            this->down();
        }

        SDL_Delay(this->loopDelay);
    }
}

void Game::up(){
    this->player->moveUp();
    if(this->currentLevel->detectCollision(this->player)) {
        this->player->destTextureParams.y += 20;
    } 

    if(this->player->destTextureParams.y < -10) {
        if(currentLevel->upNumber != none) {
            addLevel(currentLevel->upNumber);
            this->player->destTextureParams.y = 500;
        }

        this->player->destTextureParams.y += 20;
    }
    renderView();
}

void Game::down(){
    this->player->moveDown();                    
    if(this->currentLevel->detectCollision(this->player)) {
        this->player->destTextureParams.y -= 20;
    } 

    if(this->player->destTextureParams.y > 500) {
        if(currentLevel->downNumber != none) {
            addLevel(currentLevel->downNumber);
            this->player->destTextureParams.y = -10;
        } 

        this->player->destTextureParams.y -= 50;
    }
    renderView();
}

void Game::right(){
    this->player->moveRight();
    if(this->currentLevel->detectCollision(this->player)) {
        this->player->destTextureParams.x -= 20;
    } 

    if(this->player->destTextureParams.x > 600) {
        if(currentLevel->rightNumber != none) {
            addLevel(currentLevel->rightNumber);
            this->player->destTextureParams.x = -10;                            
        }

        this->player->destTextureParams.x -= 50;
    }
    renderView();
}

void Game::left(){
    this->player->moveLeft();
    if(this->currentLevel->detectCollision(this->player)) {
        this->player->destTextureParams.x += 20;
    } 

    if(this->player->destTextureParams.x < -10) {
        if(currentLevel->leftNumber != none) {
            addLevel(currentLevel->leftNumber);
            this->player->destTextureParams.x = 500;             
        }

        this->player->destTextureParams.x += 20;
    }
    renderView();
}

void Game::attack(){
    this->player->attack();
    this->currentLevel->detectCollision(this->player);
        
    renderView();
    SDL_Delay(this->loopDelay);
    this->player->position();
}
