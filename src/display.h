#ifndef DISPLAY_H
#define DISPLAY_H

#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))
#define DISPLAY_EMPTY_CELL ' '
#define DISPLAY_SNAKE_HEAD_CELL '@'
#define DISPLAY_SNAKE_BODY_CELL '#'
#define DISPLAY_SNAKE_DEAD_CELL 'X'
#define DISPLAY_FOOD_CELL '*'

typedef struct DisplayWindow {
    unsigned short int width;
    unsigned short int height;
} DisplayWindow;

DisplayWindow* init_display(unsigned short int, unsigned short int);
void free_display(DisplayWindow*);
void display_clear_cells(DisplayWindow*);
void display_set_cell(DisplayWindow*, unsigned short int, unsigned short int, const char);

#endif