/*
Grid of Points
Author: Omgeta
Date: 8/12/2021
*/
#include <stdlib.h>
#include "grid.h"

Grid* init_grid(unsigned short row_size, unsigned short col_size) {
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

// TODO: REALLY SLOW! keep an updated free space list in memory?
PointQueue* grid_empty_points(Grid* grid) {
    PointQueue* empty_points_queue = init_queue();

    for (unsigned short x = 0; x < grid->row_size; x++) {
        for (unsigned short y = 0; y < grid->col_size; y++) {
            Point p = (Point){x, y};
            if (!(point_eq(p, grid->food) || queue_includes(grid->snake->body_queue, p))) {
                queue_enqueue(empty_points_queue, p);
            }
        }
    }

    return empty_points_queue;
}

Point grid_spawn_food(Grid* grid) {
    // Select random point from the list of free points
    PointQueue* empty_points_queue = grid_empty_points(grid);
    unsigned short r = rand() % queue_size(empty_points_queue);
    Point food_point = queue_get(empty_points_queue, r);

    free_queue(empty_points_queue);

    return food_point;
}

Snake* grid_spawn_snake(Grid* grid) {
    // Select random starting x, y padded
    unsigned short x = rand() % (grid->row_size - PADDING) + (PADDING + 1);
    unsigned short y = rand() % (grid->col_size - PADDING) + (PADDING + 1);
    Point start_point = (Point){x, y};

    // Select random dir;
    int dir = rand() % (4);

    Snake* snake = init_snake(start_point, dir);
    return snake;
}

int grid_contains_snake(Grid* grid) {
    Point snake_head = grid->snake->body_queue->tail->point;
    return (snake_head.x >=0 && snake_head.x < grid->row_size) &&
            (snake_head.y >=0 && snake_head.y < grid->col_size);
}



