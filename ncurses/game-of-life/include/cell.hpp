#ifndef CELL_H
#define CELL_H

#include <ncurses.h>
#include <ncurses-core.hpp>

class Cell {
    public :
        Cell();
        Cell(int state, int x, int y);
        ~Cell();

        int state;
        int x;
        int y;

        void display();       
        void cleanUp();
        void log();
};

#endif