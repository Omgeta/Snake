#ifndef GRID_H
#define GRID_H
#include "point.h" //protected by header guard
#include "snake.h"

typedef struct Grid2D {
    unsigned short int row_size;
    unsigned short int col_size;

    Point food;
    Snake* snake;
} Grid;

static const char GRID_EMPTY_CELL = ' ';
static const char GRID_FOOD_CELL = 'F';
static const char GRID_SNAKE_CELL = 'S';

Grid* init_grid(unsigned short int, unsigned short int);
void free_grid(Grid*);
PointQueue* get_empty_cells(Grid*);
Point spawn_food(Grid*);

#endif