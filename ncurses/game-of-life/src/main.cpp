#include <ncurses.h>
#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <ncurses-core.hpp>
#include <game.hpp>
#include <plateau.hpp>

int main(int argv, char** argc) {
    std::cout << "Game of Life" << std::endl;

    //usleep(1000000);

    NcursesCore::getInstance()->init();

    Game* game = new Game();
    Plateau* plateau = new Plateau();
    game->plateau = plateau;
    game->run();
    game->close();

    return EXIT_SUCCESS;
}