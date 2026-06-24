#include <ncurses.h>
#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <ncurses-core.hpp>
#include <game.hpp>
#include <board.hpp>

int main(int argv, char** argc) {
    std::cout << "Game of Life" << std::endl;

    //usleep(1000000);

    NcursesCore::getInstance()->init();

    Game* game = new Game();
    Board* board = new Board();
    game->board = board;
    game->run();
    game->close();

    return EXIT_SUCCESS;
}