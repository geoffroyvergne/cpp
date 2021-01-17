#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <game.hpp>

int main(int argc, char** argv) {
    Game *game = new Game();
    SDL_Log("%s", game->name.c_str());

    game->intro = new Message(game->render, "../assets/Pretendo.ttf");

    game->player = new Player(game->render);
    game->player->sdl_texture = IMG_LoadTexture(game->render, "../assets/player.png");

    game->startLoop();
    
    delete game;

    return EXIT_SUCCESS;
}
