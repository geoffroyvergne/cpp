#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <game.hpp>

int main(int argc, char** argv) {
    Game *game = new Game();
    SDL_Log("%s", game->name.c_str());

    game->init();
    game->sdl_texture_items = IMG_LoadTexture(game->render, "../assets/items.png");
    
    game->player = new Player(game->render);
    game->player->sdl_texture = IMG_LoadTexture(game->render, "../assets/link.png");

    game->addLevel(h08);

    game->startLoop();
    
    delete game;

    return EXIT_SUCCESS;
}

