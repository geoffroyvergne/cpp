#ifndef PLATEAU_H
#define PLATEAU_H

#include <array>
#include <ncurses.h>
#include <iostream>
#include <cell.hpp>

class Plateau {
    public :
        Plateau();
        ~Plateau(); 

        //std::vector<std::vector<std::string>> plateau_array;
        std::vector<std::vector<Cell*>> plateau_array;
        //std::vector<std::vector<Cell*>> temp_plateau_array;

        void display_plateau();
        void init_plateau();
        void update_plateau();
        int checkCellEnvironment(const int x, const int y, const int state);
        int randomState();
};

#endif