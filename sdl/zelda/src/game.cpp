#include <iostream>
#include <SDL.h>
#include <game.hpp>
#include <sprite.hpp>
#include <sprite-type.hpp>

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

    //SDL_SetRenderDrawColor(render, 252, 216, 168, 255);
    //SDL_RenderClear(render);
	//sSDL_RenderPresent(render); 
}

void Game::renderView() {
    SDL_RenderClear(render);        
        this->currentLevel->display();
        this->player->display();
    SDL_RenderPresent(render);
}

void Game::startLoop() {
    int active = 1;
    SDL_Event e;
    while (active) {
        while (SDL_PollEvent(&e)) {          
            //if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE || e.key.keysym.sym == SDLK_q) {
            if (e.type == SDL_QUIT) {
                active = 0;
                SDL_Log("Quit");
                break;
            }

            renderView();

            switch( e.type ) {
                //case SDL_KEYUP:
                    /*if (e.key.keysym.sym == SDLK_RETURN) {
                        //this->player->endAttack();
                        //renderView();
                        
                        if(player->playerDirection == up) player->destTextureParams.y += 50;
                        if(player->playerDirection == left) player->destTextureParams.x +=50;  
                        break;
                    }
                    break;*/
                    
                case SDL_KEYDOWN:
                    if (e.key.keysym.sym == SDLK_RETURN) {
                        this->player->attack();
                        renderView();
                        SDL_Delay(this->loopDelay);
                        this->player->position();
                    }

                    if (e.key.keysym.sym == SDLK_UP) {
                        this->player->moveUp();
                    }

                    if (e.key.keysym.sym == SDLK_DOWN) {
                        this->player->moveDown();
                    }

                    if (e.key.keysym.sym == SDLK_LEFT) {
                        this->player->moveLeft();
                    }

                    if (e.key.keysym.sym == SDLK_RIGHT) {
                        this->player->moveRight();
                    }
                    //break;

                break;
            }
        
        }
        SDL_Delay(this->loopDelay);
    }
}

Sprite* Game::getSprite(SpriteType type, int x, int y) {
    switch(type) {
        case door : 
            {
                Sprite *sprite = new Sprite(render, currentLevel->sdl_texture);
                sprite->srcTextureParams = { 362, 164,  4, 4 };
                sprite->destTextureParams = { x, y,  50, 50 };

                return sprite;
            }
        break; 
        case green_rock : 
            {
                Sprite *sprite = new Sprite(render, currentLevel->sdl_texture);
                sprite->srcTextureParams = { 355, 107,  15, 16 };
                sprite->destTextureParams = { x, y,  50, 50 };

                return sprite;
            }
        break; 
        case green_rock_corner_low_right : 
            {
                Sprite *sprite = new Sprite(render, currentLevel->sdl_texture);
                sprite->srcTextureParams = { 371, 107,  15, 16 };
                sprite->destTextureParams = { x, y,  50, 50 };

                return sprite;
            }
        break;        
    };
}

/*void Game::addSprite(int x, int y, SpriteType type) {

}*/

void Game::addSpritesLevel() {
    int spriteSize = 50;

    // green_rock
    for(int i = 0; i<5; i++) {
        if(i==0) {
            for(int j=0; j<7; j++) {
                currentLevel->spriteList.push_back(getSprite(green_rock, (j) * spriteSize, i * spriteSize));
            }
        }
        if(i==1) {
            for(int j=0; j<6; j++) {
                if(j==4) continue;
                currentLevel->spriteList.push_back(getSprite(green_rock, j * spriteSize, i * spriteSize));
            }
        }
        if(i==2) {
            for(int j=0; j<3; j++) {
                currentLevel->spriteList.push_back(getSprite(green_rock, j * spriteSize, i * spriteSize));
            }
        }
        if(i==3) {
            for(int j=0; j<2; j++) {
                currentLevel->spriteList.push_back(getSprite(green_rock, j * spriteSize, i * spriteSize));
            }
        }
        if(i==4) {
            for(int j=0; j<1; j++) {
                currentLevel->spriteList.push_back(getSprite(green_rock, j * spriteSize, i * spriteSize));
            }
        }
    }

    // green_rock_corner_low_right
    for(int i = 0; i<5; i++) {
        if(i==1) {            
            currentLevel->spriteList.push_back(getSprite(green_rock_corner_low_right, 300, i * spriteSize));
        }
        if(i==2) {            
            currentLevel->spriteList.push_back(getSprite(green_rock_corner_low_right, 150, i * spriteSize));
        }
        if(i==3) {            
            currentLevel->spriteList.push_back(getSprite(green_rock_corner_low_right, 100, i * spriteSize));
        }
        if(i==4) {            
            currentLevel->spriteList.push_back(getSprite(green_rock_corner_low_right, 50, i * spriteSize));
        }
    }

    // door
    currentLevel->spriteList.push_back(getSprite(door, 200, 50));
}

void Game::cleanup() {
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
	SDL_Quit();
}