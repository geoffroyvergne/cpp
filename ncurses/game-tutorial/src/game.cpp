#include <unistd.h>
#include <ncurses.h>

#include <cstdint>
#include <string>

#include <iostream>

#include <game.hpp>

struct {
    vec2i pos;
    char disp_char;
} player;

WINDOW* wnd;

WINDOW* init() {
    wnd = initscr();

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

    return wnd;
}

void draw_box(WINDOW *) {
    // draw box around screen
    attron(A_BOLD);
    box(wnd, 0, 0);
    attroff(A_BOLD);
}

void run(WINDOW *) {

    player.disp_char = 'o';
    player.pos = {10, 5};

    //mvaddch(player.pos.y, player.pos.x, player.disp_char);
    //move(5, 5);

    /*std::string text = "Hello world!";
    for(size_t i = 0; i < text.size(); i++) {
        addch(text[i]);
        addch(' ');
    }*/

    //usleep(10000000);
    //refresh();

    int in_char;

    bool exit_requested = false;

    while(1) {
        in_char = wgetch(wnd);

        clear();
        //mvaddch(player.pos.y, player.pos.x, ' ');
        draw_box(wnd);

        switch(in_char) {
            case 'q':
                exit_requested = true;
                break;
            case KEY_UP:
            case 'w':
                if(player.pos.y > 1) player.pos.y -= 1;                   
                break;
            case KEY_DOWN:
            case 's':
                if(player.pos.y < LINES-2) player.pos.y += 1;        
                break;
            case KEY_LEFT:
            case 'a':
                if(player.pos.x > 1) player.pos.x -= 1;                
                break;
            case KEY_RIGHT:
            case 'd':
                if(player.pos.x < COLS-2) player.pos.x += 1;    
                break;
            case KEY_RESIZE:
                clear();
                init();
                break;
            case 'r':
                player.disp_char = 'o';
                break;
            case 'f':
                player.disp_char = '#';
                break;
            default:
                break;
        }

        mvaddch(player.pos.y, player.pos.x, player.disp_char);
            
        std::string position = 
        "Cursor Position : " + std::to_string(player.pos.x) + " - " + std::to_string(player.pos.y) + 
        " Screen Size : " + std::to_string(COLS) + " - " + std::to_string(LINES);

        mvaddstr(0, COLS /2 - position.size()/2, position.c_str());

        if(exit_requested) break;

        usleep(10000); // 10 ms

        refresh();
        
    }
}

void close() {
    endwin();
}
