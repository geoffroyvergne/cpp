#include <iostream>
#include <SDL.h>
#include <game.hpp>
#include <sprite.hpp>
#include <sprite-type.hpp>
#include <levels.hpp>

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
                        if(this->currentLevel->detectCollision(this->player)) {
                            this->player->destTextureParams.y += 20;
                        } 

                        if(this->player->destTextureParams.y < -10) {
                            if(currentLevel->up != NULL) {
                                this->player->destTextureParams.y = 500;
                                currentLevel = currentLevel->up;
                            }

                            this->player->destTextureParams.y += 20;
                        }
                        //break;
                    }

                    if (e.key.keysym.sym == SDLK_DOWN) {    
                        this->player->moveDown();                    
                        if(this->currentLevel->detectCollision(this->player)) {
                            this->player->destTextureParams.y -= 20;
                        } 

                        if(this->player->destTextureParams.y > 500) {
                            if(currentLevel->down != NULL) {
                                this->player->destTextureParams.y = -10;
                                currentLevel = currentLevel->down;
                            } 

                            this->player->destTextureParams.y -= 50;
                        }
                        
                        //break;
                    }

                    if (e.key.keysym.sym == SDLK_LEFT) {
                        this->player->moveLeft();
                        if(this->currentLevel->detectCollision(this->player)) {
                            this->player->destTextureParams.x += 20;
                        } 

                        if(this->player->destTextureParams.x < -10) {
                            if(currentLevel->left != NULL) {
                                this->player->destTextureParams.x = 522;                            
                                currentLevel = currentLevel->left;
                            }

                            this->player->destTextureParams.x += 20;
                        }

                        //break;
                    }

                    if (e.key.keysym.sym == SDLK_RIGHT) {
                        this->player->moveRight();
                        if(this->currentLevel->detectCollision(this->player)) {
                            this->player->destTextureParams.x -= 20;
                        } 
                
                        if(this->player->destTextureParams.x > 522) {
                            if(currentLevel->right != NULL) {
                                this->player->destTextureParams.x = -10;                            
                                currentLevel = currentLevel->right;
                            }

                            this->player->destTextureParams.x -= 50;
                        }
                        //break;
                    }
                    break;

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
                Sprite *sprite = new Sprite(render, sdl_texture_overworld);
                sprite->srcTextureParams = { 362, 164,  4, 4 };
                sprite->destTextureParams = { x, y,  50, 50 };
                sprite->collide = false;

                return sprite;
            }
        break; 
        case green_rock : 
            {
                Sprite *sprite = new Sprite(render, sdl_texture_overworld);
                sprite->srcTextureParams = { 355, 107,  15, 16 };
                sprite->destTextureParams = { x, y,  50, 50 };

                return sprite;
            }
        break; 
        case green_rock_corner_low_right : 
            {
                Sprite *sprite = new Sprite(render, sdl_texture_overworld);
                sprite->srcTextureParams = { 371, 107,  15, 16 };
                sprite->destTextureParams = { x, y,  50, 50 };
                sprite->collide = false;

                return sprite;
            }
        break;        
    };
}

/*void Game::addSprite(int x, int y, SpriteType type) {

}*/

/*

a   a01 a02 a03 a04 a05 a06 a07 a08 a09 a10 a11 a12 a13 a14 a15 a16
b   b01 b02 b03 b04 b05 b06 b07 b08 b09 b10 b11 b12 b13 b14 b15 b16
c   c01 c02 c03 c04 c05 c06 c07 c08 c09 c10 c11 c12 c13 c14 c15 c16
d   d01 d02 d03 d04 d05 d06 d07 d08 d09 d10 d11 d12 d13 d14 d15 d16
e   e01 e02 e03 e04 e05 e06 e07 e08 e09 e10 e11 e12 e13 e14 e15 e16
f   f01 f02 f03 f04 f05 f06 f07 f08 f09 f10 f11 f12 f13 f14 f15 f16
g   g01 g02 g03 g04 g05 g06 g07 g08 g09 g10 g11 g12 g13 g14 g15 g16
h   h01 h02 h03 h04 h05 h06 h07 h08 h09 h10 h11 h12 h13 h14 h15 h16
    01  02  03  04  05  06  07  08  09  10  11  12  13  14  15  16

*/

//first level : h08 right h09 left h07 up g08 down NULL

void Game::createLevels() {    
    Level *levelh08 = new Level(render, h08, sdl_texture_overworld);
    //levelh08->sdl_texture = sdl_texture;
    currentLevel = levelh08;

    addSprites(h08);

    Level *levelh09 = new Level(render, h09, sdl_texture_overworld);
    //levelh09->sdl_texture = sdl_texture;
    addSprites(h09);

    Level *levelh07 = new Level(render, h07, sdl_texture_overworld);
    //levelh07->sdl_texture = sdl_texture;
    addSprites(h07);

    Level *levelg08 = new Level(render, g08, sdl_texture_overworld);
    //levelg08->sdl_texture = sdl_texture;
    addSprites(g08);

    levelh08->right = levelh09;
    levelh08->left = levelh07;
    levelh08->up = levelg08;

    levelh09->left = levelh08;
    levelh07->right = levelh08;
    levelg08->down = levelh08;

    
}

void Game::addSprites(Levels number) {
    int spriteSize = 50;

    switch(number) {
        case h07 : 

            break;

        case h08 : 
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

            break;

        case h09 : 

            break;

        case g08 : 

            break;
    }
}

void Game::cleanup() {
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
	SDL_Quit();
}