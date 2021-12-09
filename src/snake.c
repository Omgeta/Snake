#include <stdlib.h>
#include "snake.h"

Snake* init_snake(Point start_point, enum Direction direction) {
    Snake* snake = (Snake*) malloc(sizeof(Snake));
    snake->body_queue = init_queue();
    queue_enqueue(snake->body_queue, start_point); // Set initial head of snake
    snake->size = 2;
    snake->direction = direction;
    snake_move(snake); // Creates body for snake
    return snake;
}

void free_snake(Snake* snake) {
    free_queue(snake->body_queue);
    free(snake);
}

void snake_move(Snake* snake) {
    // Calculate next position to move to
    Point snake_head = snake->body_queue->tail->point;
    Point new_head;
    switch (snake->direction) {
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

    // Cut off end of snake if it has not grown by eating food
    queue_enqueue(snake->body_queue, new_head);
    if (snake->size < queue_size(snake->body_queue)) {
        queue_dequeue(snake->body_queue);
    }
}

int snake_collides_food(Snake* snake, Point food) {
    Point snake_head = snake->body_queue->tail->point;
    return point_eq(snake_head, food);
}

int snake_collides_self(Snake* snake) {
    Point snake_head = snake->body_queue->tail->point;
    PointNode* curr = snake->body_queue->head;
    for (unsigned short int i = 1; i < snake->size; i++) { // assumes this function is called after move
        if (point_eq(snake_head, curr->point)) {
            return 1;
        }
        curr = curr->next;
    }
    return 0;
}






