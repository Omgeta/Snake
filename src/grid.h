#ifndef GRID_H
#define GRID_H

#include <stdlib.h>
#include <stdint.h>
#include "point.h"
#include "snake.h"

typedef struct Grid2D {
    uint8_t row_size;
    uint8_t col_size;

    Point food;
    Snake* snake;
} Grid;

static const char GRID_EMPTY_CELL = ' ';
static const char GRID_FOOD_CELL = 'F';
static const char GRID_SNAKE_CELL = 'S';

Grid* init_grid(uint8_t, uint8_t);
void free_grid(Grid*);
PointQueue* grid_empty_cells(Grid*);
Point grid_spawn_food(Grid*);
Snake* grid_spawn_snake(Grid*);
int grid_contains_snake(Grid*);

#endif