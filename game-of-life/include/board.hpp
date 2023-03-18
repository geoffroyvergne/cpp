#include <iostream>
#include <array>
#include <vector> 

#ifndef BOARD
#define BOARD

struct Cell {
    int state;
    int x;
    int y;
};

enum class Type {
    none,
    empty,
    full,
    stable,
    blinker,
    ship,
};

class Board {
    public:
        Board();
        ~Board(); 

        std::vector<std::vector<int>> boardData;
        std::vector<std::vector<int>> setPattern(Type type);

        void initTable(Type type);
        void display();
        void cellsEnvironment();
        int checkCellEnvironment(int x, int y);

};

#endif

/*std::vector<std::vector<int>> vectorData = {
        {0,0,0,1,0},
        {0,0,1,0,0},
        {0,0,1,1,1},
        {0,0,0,0,0},
        {0,0,0,0,0}
    };*/

    //empty
    /*int dataTable[5][5] {
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0}
    };*/

    //ship
    /*int dataTable[5][5] {
        {0,0,0,1,0},
        {0,0,1,0,0},
        {0,0,1,1,1},
        {0,0,0,0,0},
        {0,0,0,0,0}
    };*/

    //blinker
    /*int dataTable[5][5] {
        {0,0,0,0,0},
        {0,0,1,0,0},
        {0,0,1,0,0},
        {0,0,1,0,0},
        {0,0,0,0,0}
    };*/