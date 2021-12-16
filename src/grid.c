/*
Grid of 2D points
Author: Omgeta
Date: 8/12/2021
*/
#include "grid.h"

Grid* init_grid(uint8_t row_size, uint8_t col_size) {
    Grid* grid = (Grid*)malloc(sizeof(Grid));
    grid->row_size = row_size;
    grid->col_size = col_size;

    grid->snake = grid_spawn_snake(grid);
    grid->food = grid_spawn_food(grid);

    return grid;
}

void free_grid(Grid* grid) {
    free_snake(grid->snake);
    free(grid);
}

Point grid_get_empty_point(Grid* grid) {
    // 2D array of 0s holding used points
    int** used_points = (int**)calloc(grid->row_size, sizeof(int*));
    for (uint8_t x = 0; x < grid->row_size; x++) {
        used_points[x] = (int*)calloc(grid->col_size, sizeof(int));
    }

    // Set all snake points to 1
    uint8_t counter = grid->row_size * grid->col_size;
    PointNode* curr = grid->snake->body->head;
    while (curr != NULL) {
        used_points[curr->point.x][curr->point.y] = 1;
        counter--;
        curr = curr->next;
    }

    // Generate random number
    uint8_t r = rand() % counter;

    // Find rth element and return coords
    uint8_t i = 0;
    for (uint8_t y = 0; y < grid->col_size; y++) {
        for (uint8_t x = 0; x < grid->row_size; x++) {
            if (i == r) {
                return (Point){x, y};
            }

            if (!used_points[x][y]) {
                i++; // only increment current index when after point which is free
            }
        }
    }
}

Point grid_spawn_food(Grid* grid) {
    // Select random empty point to spawn food
    Point food_point = grid_get_empty_point(grid);
    return food_point;
}

Snake* grid_spawn_snake(Grid* grid) {
    // Select random starting x, y padded
    uint8_t x = rand() % (int)(grid->row_size - 0.5*grid->row_size) + (0.25*grid->row_size);
    uint8_t y = rand() % (int)(grid->col_size - 0.5*grid->row_size) + (0.25*grid->row_size);
    Point start_point = (Point){x, y};

    // Select random init direction;
    int dir = rand() % 4;

    Snake* snake = init_snake(start_point, dir);
    return snake;
}

int grid_contains_snake(Grid* grid) {
    Point snake_head = grid->snake->body->tail->point;
    return (snake_head.x >=0 && snake_head.x < grid->row_size) &&
            (snake_head.y >=0 && snake_head.y < grid->col_size);
}



