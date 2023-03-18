#include <iostream>
#include <SDL.h>

#ifndef CELL
#define CELL

/*enum class State {
    dead,
    alive,
};*/

enum class Color {
    black
};

struct Position {
    int caseNumber;
    int x;
    int y;
};

/*struct Texture {
    int x;
    int y;
};*/

class Cell {    
    public:
        Cell();
        ~Cell();

        int state = 0;
        Position position;
        //Texture texture;

        SDL_Color color;
        //Color color;
        //int size  = 10;

        void display();
        void setColor();
        void cleanup();
};

#endif
