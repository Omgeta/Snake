#ifndef OUTPUT_H
#define OUTPUT_H

#include <stdio.h>
#include <stdlib.h>

#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))
#define EMPTY_CELL ' '
#define SNAKE_HEAD_CELL '@'
#define SNAKE_BODY_CELL '#'
#define SNAKE_DEAD_CELL 'X'
#define FOOD_CELL '*'

typedef struct OutputWindow {
    unsigned short width;
    unsigned short height;
} OutputWindow;

OutputWindow* init_output(unsigned short, unsigned short);
void free_output(OutputWindow*);
void output_clear_cells(OutputWindow*);
void output_set_cell(OutputWindow*, unsigned short, unsigned short, const char);

#endif