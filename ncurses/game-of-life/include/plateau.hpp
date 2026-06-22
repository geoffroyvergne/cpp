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

        void display_plateau();
        void fill_plateau();
        void update_plateau();
};

#endif