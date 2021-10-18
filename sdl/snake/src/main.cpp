#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <game.hpp>

int main(int argc, char** argv) {
    Game *game = new Game();
    SDL_Log("%s", game->name.c_str());

    game->init(); 
    
    std::string imagePath = "../assets/image-set.png"; 
    SDL_Texture *sdl_texture = IMG_LoadTexture(game->render, imagePath.c_str());   
    
    game->plateau = new Plateau(game->render, sdl_texture);

    game->startLoop();
    
    delete game;

    return EXIT_SUCCESS;
}
