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

	/*for (size_t i = 0; i < texturesList.size(); ++i) {
		renderSprite(texturesList[i].texture, &texturesList[i].params);
	}*/
}

void Game::cleanup() {
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

			//Levels sprites loading
			for (size_t i = 0; i < texturesList.size(); ++i) {
				//renderSprite(texturesList[i].texture, &texturesList[i].params);
				if(texturesList[i].move) {
					switch( e.type ) {
						case SDL_KEYDOWN:
							if (e.key.keysym.sym == SDLK_LEFT) {
								texturesList[i].params.x = texturesList[i].params.x +10;
							}

							if (e.key.keysym.sym == SDLK_RIGHT) {
								texturesList[i].params.x = texturesList[i].params.x -10;	
							}
					}					
				}

				SDL_RenderCopy(render, texturesList[i].texture, NULL, &texturesList[i].params);
			}

			//Mario Sprite loading
			SDL_Rect textureParams = { width/2, height-32, 16, 16 };
						
			switch( e.type ) {
				case SDL_KEYDOWN:
					if (e.key.keysym.sym == SDLK_LEFT) {
						marioFlip = SDL_FLIP_HORIZONTAL;
					}

					if (e.key.keysym.sym == SDLK_RIGHT) {
						marioFlip = SDL_FLIP_NONE;
					}

					if (e.key.keysym.sym == SDLK_UP) {
						textureParams = { width/2, height-100, 16, 16 };
					}				
			}

			Texture *marioTexture = loadTexture(image_mario, textureParams, 0);

			//SDL_RenderCopy(render, marioTexture->texture, NULL, &marioTexture->params);
			SDL_RenderCopyEx(render, marioTexture->texture, NULL , &marioTexture->params, 0.0, NULL, marioFlip);

			SDL_RenderPresent(render);
		}
		SDL_Delay(100);
	}
}

SDL_Texture* Game::loadTexture(std::string file) {
	SDL_Texture *texture = IMG_LoadTexture(render, file.c_str());
	if (texture == NULL){		
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Loading Texture %s", file.c_str());
		exit(EXIT_FAILURE);
	}
	return texture;
}

Texture* Game::loadTexture(std::string file, SDL_Rect textureParams, int move) {
	SDL_Texture *sdl_texture = IMG_LoadTexture(render, file.c_str());
	if (sdl_texture == NULL){		
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Loading Texture %s", file.c_str());
		exit(EXIT_FAILURE);
	}

	Texture *texture = new Texture();
	texture->texture = sdl_texture;
	texture->params = textureParams;
	texture->move = move;

	return texture;
}

void Game::renderSprite(SDL_Texture *texture, SDL_Rect *textureParams) {	
	SDL_RenderCopy(render, texture, NULL, textureParams);
	SDL_RenderPresent(render);
}
