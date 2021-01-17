#include <iostream>
#include <SDL.h>
#include <game.hpp>
#include <sprite.hpp>
#include <sprite-type.hpp>
#include <levels.hpp>
#include <enemy.hpp>
#include <enemy-type.hpp>

//Game::Game() {}

Game::~Game() { 
    cleanup();
}

void Game::init() {
    //Start up SDL, and make sure it went ok
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
}

void Game::renderView() {
    SDL_RenderClear(render);        
        this->currentLevel->display();
        this->player->display();
    SDL_RenderPresent(render);
}

void Game::addLevel(Levels level) {
    if(currentLevel != NULL) delete currentLevel;
    SDL_Texture *sdl_texture_overworld = IMG_LoadTexture(render, "../assets/overworld-tileset.png");
    SDL_Texture *sdl_texture_overworld_enemies = IMG_LoadTexture(render, "../assets/overworld-enemies.png");
    currentLevel = new Level(render, level, sdl_texture_overworld, sdl_texture_overworld_enemies);

    SDL_Log("Level number : %s", currentLevel->name.c_str());
}

void Game::startLoop() {
    int active = 1;
    SDL_Event e;
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    while (active) {
        while (SDL_PollEvent(&e)) {          
            //if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE || e.key.keysym.sym == SDLK_q) {
            if (e.type == SDL_QUIT) {
                active = 0;
                SDL_Log("Quit");
                break;
            }

            renderView();

            //switch( e.type ) {
                //case SDL_KEYDOWN:
                    /*if (e.key.keysym.sym == SDLK_RETURN) {
                        this->attack();
                    }

                    if (e.key.keysym.sym == SDLK_UP) {
                        this->up();
                        //break;
                    }

                    if (e.key.keysym.sym == SDLK_DOWN) {    
                        this->down();
                        //break;
                    }

                    if (e.key.keysym.sym == SDLK_LEFT) {
                        this->left();
                        //break;
                    }

                    if (e.key.keysym.sym == SDLK_RIGHT) {
                        this->right();
                        //break;
                    }
                    break;*/

                //break;
            //}
        
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
            //currentLevel = currentLevel->up;
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
            //currentLevel = currentLevel->down;
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
            //currentLevel = currentLevel->right;
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
            //currentLevel = currentLevel->left;
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

void Game::cleanup() {
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
	SDL_Quit();
}
