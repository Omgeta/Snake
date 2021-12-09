#ifndef GRID_H
#define GRID_H

#include "point.h"
#include "snake.h"
#define PADDING 3

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
PointQueue* grid_empty_cells(Grid*);
Point grid_spawn_food(Grid*);
Snake* grid_spawn_snake(Grid*);
int grid_contains_snake(Grid*);

#endif