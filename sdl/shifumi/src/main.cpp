#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include <game.hpp>
#include <player.hpp>

#include "core.hpp"

int main(int argc, char** argv) {
    Game *game = new Game();
    SDL_Log("%s", game->name.c_str());

    Core::getInstance()->init();

    game->player1 = new Player("player1", player1Type);
    game->player1->piece = new Piece(none);

    game->player2 = new Player("player2", player2Type);
    game->player2->piece = new Piece(none);
    game->player2->piece->destTextureParams.x = 300;

    game->playerNone = new Player("playerNone", playerNoneType);

    game->startLoop();    

    delete game;

    return EXIT_SUCCESS;
}
