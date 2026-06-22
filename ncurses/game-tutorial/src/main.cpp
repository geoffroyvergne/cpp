#include <ncurses.h>
#include <string>
#include <game.hpp>

int main(int argv, char** argc) {

    /*int init_status = init();

    if(init_status == 0) {
        run();
    }*/

    WINDOW* wnd = init();
    run(wnd);

    close();

    return 0;
}