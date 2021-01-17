#include <iostream>
#include <SDL.h>
#include <game.hpp>
#include <message.hpp>
#include <player.hpp>

Game::Game() { 
    init();
    
    this->sdl_texture_levels = IMG_LoadTexture(render, "../assets/levels.png");
    this->sdl_texture_enemies = IMG_LoadTexture(render, "../assets/enemies.png");

    newLevel(w11);
}

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

    TTF_Init();

    SDL_SetRenderDrawColor(render, 4, 156, 216, 255);
}

void Game::renderView() {
    SDL_RenderClear(render);        
        //displayIntro();
        displayGame();
        this->player->display();
    SDL_RenderPresent(render);
}

void Game::displayIntro() {
    if(SDL_GetTicks() < 3000) {
        if(intro != NULL) {
            SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
            
            intro->textureParams = { 128, 128,  256, 45 };
            intro->message = "Nintendo";
        }
        intro->displayMessage();
    }
}

void Game::displayGame() {
    //if(SDL_GetTicks() > 3000) {        
        SDL_SetRenderDrawColor(render, 4, 156, 216, 255);
        
        this->currentLevel->display();
    //}
}

void Game::newLevel(World world) {
    if(this->currentLevel != nullptr) delete this->currentLevel;

    currentLevel = new Level(world, render, sdl_texture_levels, sdl_texture_enemies);
}

void Game::startLoop() {
    renderView();
    int active = 1;
    SDL_Event e;
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    while (active) {
        //if(SDL_GetTicks() < 10000) renderView();
        
        this->fall(state);

        while (SDL_PollEvent(&e)) {      
            if (e.type == SDL_QUIT) {
                active = 0;
                SDL_Log("Quit");
                break;
            }

            renderView();

            switch( e.type ) {     
                
                case SDL_KEYDOWN:
                    if (e.key.keysym.sym == SDLK_RETURN) {
                        SDL_Log("SDLK_RETURN");
                        //break;
                    }

                    /*if (e.key.keysym.sym == SDLK_q) {
                        this->jump();
                        //break;
                    }*/

                    /*if (e.key.keysym.sym == SDLK_LEFT) {
                        this->left(state);
                        break;
                    }

                    if (e.key.keysym.sym == SDLK_RIGHT) {
                        this->right(state);
                        break;
                    }*/           
            }
        }

        if (state[SDL_SCANCODE_RIGHT]) {
            this->right(state);
        }

        if (state[SDL_SCANCODE_LEFT]) {
            this->left(state);
        }

        if (state[SDL_SCANCODE_UP]) {
            this->jump(state);            
        }

        /*if (state[SDL_SCANCODE_DOWN]) {
            player->moveDown();
        }*/

        SDL_Delay(this->loopDelay);
    }
}

void Game::jump(const Uint8 *state) {
    for(int i=0; i<8; i++) {
        /*if (state[SDL_SCANCODE_RIGHT]) {
            this->right(state);
            SDL_Delay(25);
        }
        if (state[SDL_SCANCODE_LEFT]) {
            this->left(state);
            SDL_Delay(25);
        }*/

        //if(! currentLevel->detectCollision(this->player)) {
            player->moveUp(30);
            renderView();
            SDL_Delay(25);
        //}
    }
    fall(state);
    //renderView();
}

void Game::left(const Uint8 *state) {    
    
    if(player->playerDirection == PlayerDirection::right || !currentLevel->detectCollision(this->player)) {
        currentLevel->moveLeft();
        player->moveLeft();
    } 
    
    renderView();
}

void Game:: right(const Uint8 *state) {
    
    if(player->playerDirection == PlayerDirection::left || !currentLevel->detectCollision(this->player)) {
        currentLevel->moveRight();
        player->moveRight();
    } 
    
    renderView();
}

void Game::fall(const Uint8 *state) {
    //for(int i=0; i<5; i++) {
    //while(player->destTextureParams.y < currentLevel->tileSize*14) {
    //while(!currentLevel->detectCollision(this->player)) {
        
    while(true) {
        if(this->player->destTextureParams.y > this->height) break;

        if(currentLevel->detectCollisionFall(this->player)) {
            //player->moveUp(30);
            break;
        } else {
            player->moveDown(30);
            renderView();
            SDL_Delay(25);
        }
    }
}

void Game::cleanup() {
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    TTF_Quit();
	SDL_Quit();
}
