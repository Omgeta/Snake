#include <stdlib.h>
#include "snake.h"

PointQueue* _init_snake_body_queue(Point, enum Direction, unsigned short);
Point _snake_new_head(PointQueue*, enum Direction);
int _snake_same_or_opp_dir(enum Direction dir1, enum Direction dir2);

Snake* init_snake(Point start_point, enum Direction direction) {
    Snake* snake = (Snake*)malloc(sizeof(Snake));
    snake->size = 2;
    snake->direction = direction;
    snake->body_queue = _init_snake_body_queue(start_point, snake->direction, snake->size);
    return snake;
}

PointQueue* _init_snake_body_queue(Point start_point, enum Direction direction, unsigned short size) {
    PointQueue* body_queue = init_queue();
    queue_enqueue(body_queue, start_point); // tail
    for (unsigned short i = 1; i < size; i++) {
        Point new_head = _snake_new_head(body_queue, direction);
        queue_enqueue(body_queue, new_head);
    }
    return body_queue;
}

void free_snake(Snake* snake) {
    free_queue(snake->body_queue);
    free(snake);
}

Point _snake_new_head(PointQueue* body_queue, enum Direction direction) {
    // Calculate next position to move to
    Point snake_head = body_queue->tail->point;
    Point new_head;
    switch (direction) {
        case LEFT:
            new_head = (Point){snake_head.x - 1, snake_head.y};
            break;
        case RIGHT:
            new_head = (Point){snake_head.x + 1, snake_head.y};  
            break;
        case UP:
            new_head = (Point){snake_head.x, snake_head.y - 1};
            break;
        case DOWN:
            new_head = (Point){snake_head.x, snake_head.y + 1};
            break;
    }
    return new_head;
}

void snake_move(Snake* snake) {
    // Get new head
    Point new_head = _snake_new_head(snake->body_queue, snake->direction);

    // Cut off tail of snake if it has not grown by eating food
    queue_enqueue(snake->body_queue, new_head);
    if (snake->size < queue_size(snake->body_queue)) {
        queue_dequeue(snake->body_queue);
    }
}

int _snake_same_or_opp_dir(enum Direction dir1, enum Direction dir2) {
    return (dir1 > 1) == (dir2 > 1);
}

void snake_turn(Snake* snake, enum Direction dir) {
    if (!(_snake_same_or_opp_dir(snake->direction, dir))) {
        snake->direction = dir;
    }
}

int snake_collides_food(Snake* snake, Point food) {
    Point snake_head = snake->body_queue->tail->point;
    return point_eq(snake_head, food);
}

int snake_collides_self(Snake* snake) {
    Point snake_head = snake->body_queue->tail->point;
    PointNode* curr = snake->body_queue->head;
    for (unsigned short i = 1; i < snake->size; i++) { // assumes this function is called after move
        if (point_eq(snake_head, curr->point)) {
            return 1;
        }
        curr = curr->next;
    }
    return 0;
}
