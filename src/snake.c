#include <stdlib.h>
#include "snake.h"

Snake* init_snake(Point start_point, enum Direction direction) {
    Snake* snake = (Snake*) malloc(sizeof(Snake));
    snake->body_queue = init_queue();
    enqueue_point(snake->body_queue, start_point); // Set head of snake
    snake->size = 1;
    snake->direction = direction;
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
    enqueue_point(snake->body_queue, new_head);
    if (snake->size < queue_size(snake->body_queue)) {
        dequeue_point(snake->body_queue);
    }
}




