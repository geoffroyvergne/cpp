#include <iostream>
#include <SDL.h>
#include <game.hpp>

int main(int argc, char** argv) {
    Game *game = new Game();
    SDL_Log("%s", game->name.c_str());

    game->init();  

    std::string imagePath = "../assets/image-set.png"; 
    SDL_Texture *sdl_texture = IMG_LoadTexture(game->render, imagePath.c_str());   
    
    game->plateau = new Plateau(game->render, sdl_texture);
    //game->plateau->addPiece(O);
    game->plateau->addCurrentPiece();

    // TODO fix it
    for(int i=0; i<4; i++) {
        game->plateau->rotateCurrentPiece();
    }

    game->startLoop();
    
    delete game;

    return EXIT_SUCCESS;
}
