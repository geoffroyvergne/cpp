#include <iostream>
#include <SDL.h>
#include <game.hpp>
#include <message.hpp>
#include <player.hpp>

int main(int argc, char** argv) {
    Game *game = new Game();
    SDL_Log("%s", game->name.c_str());

    game->init();
    game->message = new Message(game->render);
    game->player1 = new Player("player1");
    game->player2 = new Player("player1");

    game->startLoop();

    delete game;
    return EXIT_SUCCESS;
}
