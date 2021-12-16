#ifndef OUTPUT_H
#define OUTPUT_H

#include <stdio.h>
#include <stdlib.h>

#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))
#define BORDER_CELL '#'
#define EMPTY_CELL ' '
#define SNAKE_HEAD_CELL 'O'
#define SNAKE_BODY_CELL 'o'
#define SNAKE_DEAD_CELL 'X'
#define FOOD_CELL '*'

typedef struct OutputWindow {
    unsigned short width;
    unsigned short height;
} OutputWindow;

OutputWindow* init_output(unsigned short, unsigned short);
void free_output(OutputWindow*);
void output_clear_cells(OutputWindow*);
void output_draw_border(OutputWindow*);
void output_draw_grid_cell(OutputWindow*, unsigned short, unsigned short, const char);
static int _output_is_valid(OutputWindow*, unsigned short, unsigned short)
static void _output_set_cell(OutputWindow*, unsigned short, unsigned short, const char)

#endif