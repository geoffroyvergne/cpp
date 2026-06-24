#include <iostream>
#include <ncurses.h>
#include <ncurses-core.hpp>

void NcursesCore::init() { 
    std::cout << "Core Init" << std::endl;

    WINDOW* wnd = initscr();

    cbreak();
    noecho();
    clear();
    refresh();

    // enable function keys
    keypad(wnd, true);

    // disable input blocking
    nodelay(wnd, true);

    // hide cursor
    curs_set(0);

    if(!has_colors()) {
        endwin();
        printf("ERROR: Terminal does not support color.\n)");
        exit(1);
    }

    // enable color modification
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_CYAN);
    wbkgd(wnd, COLOR_PAIR(1));

    NcursesCore::window = wnd;
}

void NcursesCore::displayMessage(std::string message) {
    std::cout << message << std::endl;
}

NcursesCore* NcursesCore::getInstance() {
    if(!NcursesCore::instance) {
        NcursesCore::instance = new NcursesCore();
    }
    return instance;
}

/*std::string NcursesCore::getStr(int state) {
    switch(state) {
        case 0:
            return " ";
            break;
        case 1:
            return "#";
            break;
        default:
            return "O";
            break;
    }
}*/

WINDOW* NcursesCore::getWindow() {
    return NcursesCore::window;
}

NcursesCore* NcursesCore::instance = nullptr;