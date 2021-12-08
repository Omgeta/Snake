/*
Grid of Points
Author: Omgeta
Date: 8/12/2021
*/
#include <stdlib.h>
#include "grid.h"

Grid* init_grid(unsigned short int row_size, unsigned short int col_size) {
    Grid* grid = (Grid*)malloc(sizeof(Grid));
    grid->row_size = row_size;
    grid->col_size = col_size;

    grid->snake = init_snake(DEFAULT_SNAKE_START, DEFAULT_SNAKE_DIR);
    grid->food = spawn_food(grid);

    return grid;
}

void free_grid(Grid* grid) {
    free(grid);
}

// TODO: REALLY BAD!!! make this faster. maybe implement a free space list which changes on update?
PointQueue* get_empty_points(Grid* grid) {
    PointQueue* empty_points_queue = init_queue();

    
    for (unsigned short int x = 0; x < grid->row_size; x++) {
        for (unsigned short int y = 0; y < grid->col_size; y++) {
            Point p = (Point){x, y};
            if (!(point_eq(p, grid->food) || includes_point(grid->snake->body_queue, p))) {
                enqueue_point(empty_points_queue, p);
            }
        }
    }

    return empty_points_queue;
}

Point spawn_food(Grid* grid) {
    // Select random point from the list of free points
    PointQueue* empty_points_queue = get_empty_points(grid);
    int r = rand() % queue_size(empty_points_queue);
    Point food_point = get_point(empty_points_queue, r);

    free_queue(empty_points_queue);

    return food_point;
}



