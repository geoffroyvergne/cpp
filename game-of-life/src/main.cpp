#include <iostream>
#include <board.hpp>
#include <unistd.h>

int main(int argc, char** argv) {
    std::cout << "Game of life" << std::endl;
    Board* board = new Board();

    int iterations=10;
    board->initTable(Type::ship);

    for(int i=0; i<iterations; i++) {        
        board->display();
        if(i<iterations-1) usleep(500000);
        board->cellsEnvironment();
    }

    return EXIT_SUCCESS;
}
