#include <iostream>
#include <SDL.h>

#include <game.hpp>

int main(int argc, char** argv) {
    SDL_Log("SDL Hello World!");

    Game *game = new Game();
    game->init();
    game->loadBackground("../assets/nintendo-logo.jpg");

    game->startLoop();

    SDL_DestroyTexture(game->tex);
    free(game);
    
    return EXIT_SUCCESS;
}
