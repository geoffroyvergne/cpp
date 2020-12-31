#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

#include <game.hpp>
#include <settings.hpp>

void Game::init(std::string windowTitle, int screenWidth, int screenHeight) {
    SDL_Log("Init game");

    //First we need to start up SDL, and make sure it went ok
	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not initialize SDL: %s\n", SDL_GetError());
        
		exit(EXIT_FAILURE);
	}

	// Create window
	window = SDL_CreateWindow(windowTitle.c_str(), 100, 100, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	if (window == NULL) {cleanup(); exit(EXIT_FAILURE);}

	// Create render
	render = SDL_CreateRenderer(window, -1, 0);
	//render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);	
	if (render == NULL) {cleanup(); exit(EXIT_FAILURE);}

	// Background color 049CD8 4, 156, 216
	SDL_SetRenderDrawColor(render, 4, 156, 216, 255);
	SDL_RenderClear(render);
	SDL_RenderPresent(render);
}

void Game::cleanup() {
	//Clean textures
	for (size_t i = 0; i < texturesList.size(); ++i) {
		SDL_DestroyTexture(texturesList[i].texture);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::startLoop() {
	int moveOffset = 0;
	int active = 1;
	SDL_RendererFlip marioFlip = SDL_FLIP_NONE;
	SDL_Event e;
	while (active) {
		while (SDL_PollEvent(&e)) {	
			if (e.type == SDL_QUIT) {
				active = 0;
				SDL_Log("Quit\n");
			}

			SDL_RenderClear(render);

			this->loadLevelSprites(&e);
			this->loadMarioSprite(&e, &marioFlip);
			
			SDL_RenderPresent(render);
		}
		SDL_Delay(LOOP_DELAY);
	}
}

void Game::loadMarioSprite(SDL_Event *e, SDL_RendererFlip *marioFlip) {
	//Mario Sprite loading
	SDL_Rect textureParams = { width/2, height-32, 16, 16 };
				
	switch( e->type ) {
		case SDL_KEYDOWN:
			// Left Arrow
			if (e->key.keysym.sym == SDLK_LEFT) {
				*marioFlip = SDL_FLIP_HORIZONTAL;
				break;
			}

			// Right Arrow
			if (e->key.keysym.sym == SDLK_RIGHT) {
				*marioFlip = SDL_FLIP_NONE;
				break;
			}

			// Up Arrow
			if (e->key.keysym.sym == SDLK_UP) {
				textureParams = { width/2, height-100, 16, 16 };
				
				break;
			}				

			// Down Arrow
			if (e->key.keysym.sym == SDLK_DOWN) {
				SDL_Log("SDLK_DOWN\n");
				break;
			}
			break;
	}

	this->marioTexture = loadTexture(image_mario, "mario", textureParams, 0, 0);

	//SDL_RenderCopy(render, marioTexture->texture, NULL, &marioTexture->params);
	SDL_RenderCopyEx(render, this->marioTexture->texture, NULL , &this->marioTexture->params, 0.0, NULL, *marioFlip);
}

Texture* Game::loadTexture(std::string file, std::string name, SDL_Rect textureParams, int move, int colide) {
	SDL_Texture *sdl_texture = IMG_LoadTexture(render, file.c_str());

	if (sdl_texture == NULL){		
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Loading Texture %s", file.c_str());
		exit(EXIT_FAILURE);
	}

	Texture *texture = new Texture();
	texture->name = name;
	texture->texture = sdl_texture;
	texture->params = textureParams;
	texture->move = move;
	texture->colide = colide;

	return texture;
}

void Game::loadLevelSprites(SDL_Event *e) {
	//Levels sprites loading
	for (size_t i = 0; i < texturesList.size(); ++i) {

		//TODO colisions
		if(texturesList[i].colide) {
			if(marioTexture != NULL) {
				collision = SDL_HasIntersection(&texturesList[i].params, &marioTexture->params);

				if (collision) {
					SDL_Log("collision detected %s", texturesList[i].name.c_str());
				}
			}
		}
		
		if(texturesList[i].move) {
			switch( e->type ) {
				case SDL_KEYDOWN:
					if (e->key.keysym.sym == SDLK_LEFT) {
						texturesList[i].params.x = texturesList[i].params.x +10;
						break;
					}

					if (e->key.keysym.sym == SDLK_RIGHT) {
						texturesList[i].params.x = texturesList[i].params.x -10;
						break;
					}
					break;
			}					
		}

		SDL_RenderCopy(render, texturesList[i].texture, NULL, &texturesList[i].params);
	}
}

void Game::loadLevel(int level) {
	SDL_Log("Load level %d", level);
	//Load textures
    SDL_Rect textureParams;

    //Clouds
    for(int i=0; i<10; i++) {
        textureParams = { i* 100, rand() % 100 +10,  32, 24 };
        this->texturesList.push_back(*this->loadTexture(image_cloud, "cloud",textureParams, 1, 0));
    }

    //Hills
    for(int i=0; i<5; i++) {
        textureParams = { i* (rand() % 100 + 210), height-32-16, 80, 35 };
        this->texturesList.push_back(*this->loadTexture(image_hill, "hill", textureParams, 1, 0));
    }

    //Bush
    for(int i=0; i<10; i++) {
        textureParams = { i* (rand() % 100 + 110), height-32, 32, 16 };
        this->texturesList.push_back(*this->loadTexture(image_bush, "bush", textureParams, 1, 0));
    }

    //Pipes
    for(int i=0; i<5; i++) {
        textureParams = { i* (rand() % 100 + 210), height-32-16, 32, 32 };
        this->texturesList.push_back(*this->loadTexture(image_pipe, "pipe", textureParams, 1, 1));
    }

    //Questions mark
    textureParams = { 200, 100, 16, 16 };
    this->texturesList.push_back(*this->loadTexture(image_question_mark, "question-mark", textureParams, 1, 1));

    //Ground
    for(int i=0; i<100; i++) {
        textureParams = { i*16, height, 16, 16 };
        this->texturesList.push_back(*this->loadTexture(image_ground, "ground", textureParams, 1, 1));

        textureParams = { i*16, height-16, 16, 16 };
        this->texturesList.push_back(*this->loadTexture(image_ground, "ground", textureParams, 1, 1));
    }
}
