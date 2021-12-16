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

// TODO: Change to free space bitmap!!! URGENT
PointQueue* grid_empty_points(Grid* grid) {
    PointQueue* empty_points_queue = init_queue();

    for (uint8_t x = 0; x < grid->row_size; x++) {
        for (uint8_t y = 0; y < grid->col_size; y++) {
            Point p = (Point){x, y};
            if (!(point_eq(p, grid->food) || queue_includes(grid->snake->body, p))) {
                queue_enqueue(empty_points_queue, p);
            }
        }
    }

    return empty_points_queue;
}

Point grid_spawn_food(Grid* grid) {
    // Select random point from the list of free points
    PointQueue* empty_points_queue = grid_empty_points(grid);
    uint8_t r = rand() % queue_size(empty_points_queue);
    Point food_point = queue_get(empty_points_queue, r);

    free_queue(empty_points_queue);

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



