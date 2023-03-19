#include <iostream>
#include <array>
#include <vector>
#include <cell.hpp>

#ifndef BOARD
#define BOARD

enum class Pattern {
    none,
    empty,
    full,
    stable,
    blinker,
    glider,
    light_glider_rocket,
    glider_rocket,
    bloc,
    frog,
    boat,
    light_ship,
    ship
};

class Board {
    public:
        Board();
        ~Board();

        std::vector<std::vector<Cell>> boardData;

        std::vector<std::vector<int>> setPattern(Pattern pattern);
        void initTable(Pattern pattern);
        void display();
        void displayCells();
        void cellsEnvironment();
        int checkCellEnvironment(int x, int y);
};

#endif
