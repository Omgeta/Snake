/*
Snake represented by a PointQueue with a changeable direction
Author: Omgeta
Date: 9/12/2021
*/
#include <stdlib.h>
#include "snake.h"

Snake* init_snake(Point start_point, enum Direction direction) {
    Snake* snake = (Snake*)malloc(sizeof(Snake));
    snake->direction = direction;
    snake->body = _init_snake_body(start_point, snake->direction, 2);
    return snake;
}

void free_snake(Snake* snake) {
    free_queue(snake->body);
    free(snake);
}

unsigned short snake_length(Snake* snake) {
    return queue_size(snake->body);
}

void snake_turn(Snake* snake, enum Direction dir) {
    // Only makes valid turns
    if (!_snake_same_or_opp_dir(snake->direction, dir)) {
        snake->direction = dir;
    }
}

void snake_add_head(Snake* snake) {
    // Enqueue new head onto body using the current direction
    Point next_head = _snake_next_head(snake, snake->direction);
    queue_enqueue(snake->body, next_head);
}

void snake_remove_tail(Snake* snake) {
    queue_dequeue(snake->body);
}

int snake_collides_food(Snake* snake, Point food) {
    Point snake_head = snake->body->tail->point;
    return point_eq(snake_head, food);
}

int snake_collides_self(Snake* snake) {
    Point snake_head = snake->body->tail->point;

    // Iterates through all others body points to check for collisions with head 
    PointNode* curr = snake->body->head;
    for (unsigned short i = 1; i < snake->size; i++) { // assumes this function is called after move
        if (point_eq(snake_head, curr->point)) {
            return 1;
        }
        curr = curr->next;
    }
    return 0;
}

static PointQueue* _init_snake_body(Point start_point, enum Direction direction, unsigned short size) {
    // Creates a body (PointQueue*) by growing new heads for the specified size and direction
    PointQueue* body = init_queue();
    queue_enqueue(body, start_point); // tail
    for (unsigned short i = 1; i < size; i++) {
        Point next_head = snake_next_head(body, direction);
        queue_enqueue(body, next_head);
    }
    return body;
}

static Point _snake_next_head(PointQueue* body, enum Direction direction) {
    // Calculate next position to move to
    Point snake_head = body->tail->point;
    Point next_head;
    switch (direction) {
        case LEFT:
            next_head = (Point){snake_head.x - 1, snake_head.y};
            break;
        case RIGHT:
            next_head = (Point){snake_head.x + 1, snake_head.y};  
            break;
        case UP:
            next_head = (Point){snake_head.x, snake_head.y - 1};
            break;
        case DOWN:
            next_head = (Point){snake_head.x, snake_head.y + 1};
            break;
    }
    return next_head;
}

static int _snake_same_or_opp_dir(enum Direction dir1, enum Direction dir2) {
    // LEFT = 0, RIGHT = 1, UP = 2, DOWN = 3
    // Same or opposite directions occur when both are on one of the sides >1 or <1
    return (dir1 > 1) == (dir2 > 1);
}
