#include <iostream>
#include <array>
#include <vector>
#include <cell.hpp>

#ifndef BOARD
#define BOARD

enum class Pattern {
    none,
    random,
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

struct BoardSize {
    int x;
    int y;
};

class Board {
    public:
        Board(Pattern pattern);
        ~Board();

        Pattern pattern;

        std::vector<std::vector<Cell>> boardData;

        std::vector<std::vector<int>> setPattern();
        BoardSize initTable();
        std::vector<std::vector<int>> initRandomTable();
        void display();
        void displayCells();
        void cellsEnvironment();
        int checkCellEnvironment(int x, int y);
};

#endif
