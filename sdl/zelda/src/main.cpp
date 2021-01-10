#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <game.hpp>

int main(int argc, char** argv) {
    Game *game = new Game();
    SDL_Log("%s", game->name.c_str());

    game->init();    
    
    game->player = new Player(game->render);
    game->player->sdl_texture = IMG_LoadTexture(game->render, "../assets/link.png");

    SDL_Texture *sdl_texture_overworld = IMG_LoadTexture(game->render, "../assets/overworld-tileset.png");
    game->sdl_texture_overworld = sdl_texture_overworld;

    game->createLevels();

    game->startLoop();
    
    delete game;

    return EXIT_SUCCESS;
}

