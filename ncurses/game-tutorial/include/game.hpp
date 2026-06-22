#ifndef GAME_H
#define GAME_H

typedef struct {
    int x;
    int y;
} vec2ui;

typedef struct {
    int x;
    int y;
} vec2i;

WINDOW * init();
void draw_box(WINDOW *);
void run(WINDOW *);
void close();

#endif
