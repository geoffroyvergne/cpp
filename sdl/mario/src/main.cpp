#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <game.hpp>

int main(int argc, char** argv) {
    Game *game = new Game();
    SDL_Log("%s", game->name.c_str());

    game->intro = new Message(game->render, "../assets/Pretendo.ttf");

    game->startLoop();
    
    delete game;

    return EXIT_SUCCESS;
}
