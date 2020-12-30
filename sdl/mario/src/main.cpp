#include <iostream>
#include <vector>

#include <SDL.h>

#include <settings.hpp>
#include <game.hpp>

int main(int argc, char** argv) {
    SDL_Log("Mario!");

    Game *game = new Game();

    game->init("Mario", width, height);

    //Load textures
    SDL_Rect textureParams;

    //Clouds
    for(int i=0; i<10; i++) {
        textureParams = { i* 100, rand() % 100 +10,  32, 24 };
        game->texturesList.push_back(*game->loadTexture(image_cloud, textureParams, 1));
    }

    //Hills
    for(int i=0; i<5; i++) {
        textureParams = { i* (rand() % 100 + 210), height-32-16, 80, 35 };
        game->texturesList.push_back(*game->loadTexture(image_hill, textureParams, 1));
    }

    //Bush
    for(int i=0; i<10; i++) {
        textureParams = { i* (rand() % 100 + 110), height-32, 32, 16 };
        game->texturesList.push_back(*game->loadTexture(image_bush, textureParams, 1));
    }

    //Pipes
    for(int i=0; i<5; i++) {
        textureParams = { i* (rand() % 100 + 210), height-32-16, 32, 32 };
        game->texturesList.push_back(*game->loadTexture(image_pipe, textureParams, 1));
    }

    //Questions mark
    textureParams = { 200, 100, 16, 16 };
    game->texturesList.push_back(*game->loadTexture(image_question_mark, textureParams, 1));

    //Ground
    for(int i=0; i<100; i++) {
        textureParams = { i*16, height, 16, 16 };
        game->texturesList.push_back(*game->loadTexture(image_ground, textureParams, 1));

        textureParams = { i*16, height-16, 16, 16 };
        game->texturesList.push_back(*game->loadTexture(image_ground, textureParams, 1));
    }

    //Mario
    //textureParams = { width/2, height-32, 16, 16 };
    //game->texturesList.push_back(*game->loadTexture(image_mario, textureParams, 0));

    game->startLoop();

    game->cleanup();
    free(game);

    return EXIT_SUCCESS;
}
