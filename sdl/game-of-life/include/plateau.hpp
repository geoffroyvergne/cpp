#include <iostream>
#include <array>
#include <cell.hpp>

#ifndef PLATEAU
#define PLATEAU

enum class Pattern {
    none,
    random,
    symetric_random,
    glider,
    spaceship,

};

class Plateau {
    public:
        Plateau();
        ~Plateau();  

        std::array<std::array<Cell*, 5>, 5> cellTable;

        //empty
        /*int dataTable[5][5] {
            {0,0,0,0,0},
            {0,0,0,0,0},
            {0,0,0,0,0},
            {0,0,0,0,0},
            {0,0,0,0,0}
        };*/

        //full
        /*int dataTable[5][5] {
            {1,1,1,1,1},
            {1,1,1,1,1},
            {1,1,1,1,1},
            {1,1,1,1,1},
            {1,1,1,1,1}
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
        int dataTable[5][5] {
            {0,0,0,0,0},
            {0,0,1,0,0},
            {0,0,1,0,0},
            {0,0,1,0,0},
            {0,0,0,0,0}
        };

        /*int dataTable[3][3] {            
            {0,0,0},
            {1,1,1},
            {0,0,0}           
        };*/

        void clearCellTable();

        void display();
        void displayCells();
        void cellsEnvironment();
        void checkCellEnvironment(Cell* cell);
};

#endif
