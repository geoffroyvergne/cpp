#include <iostream>
#include <SDL.h>
#include <game.hpp>

int main(int argc, char** argv) {
    Game *game = new Game();
    SDL_Log("%s", game->name.c_str());

    game->init();     
    
    game->plateau = new Plateau(game->render);
    //game->plateau->addPiece(O);
    game->plateau->addCurrentPiece();

    for(int i=0; i<4; i++) {
        game->plateau->rotateCurrentPiece();
    }

    game->startLoop();
    
    delete game;

    return EXIT_SUCCESS;
}
