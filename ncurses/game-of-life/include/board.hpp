#ifndef PLATEAU_H
#define PLATEAU_H

#include <array>
#include <ncurses.h>
#include <iostream>

class Board {
    public :
        Board();
        ~Board(); 

        std::vector<std::vector<int>> current;
        std::vector<std::vector<int>> next;

        int iterations = 0;
        int running = 1;

        void display(); 

        void clear();

        void randomize(int density = 20);

        void update();
        int randomState();

        void toggleCell(int x, int y);
        int aliveCount() const;

        int countAliveNeighbours(int x, int y);
        int nextState(int x, int y);

        void addBlinker(int x = 10, int y = 10);
        void addGlider(int x = 10, int y = 10);
        void addPulsar(int x = 10, int y = 10);
};

#endif