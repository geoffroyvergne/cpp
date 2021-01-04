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
    game->player1 = new Player("player1", player1Type);
    game->player1->piece = new Piece(game->render, none);

    game->player2 = new Player("player2", player2Type);
    game->player2->piece = new Piece(game->render, none);
    game->player2->piece->textureParams.x = 300;

    game->playerNone = new Player("playerNone", playerNoneType);

    game->startLoop();

    delete game;
    return EXIT_SUCCESS;
}
