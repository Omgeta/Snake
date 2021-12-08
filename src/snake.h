#ifndef SNAKE_H
#define SNAKE_H
#include "point.h"

#define DEFAULT_SNAKE_START (Point){1, 0}
#define DEFAULT_SNAKE_DIR UP

enum Direction {LEFT, RIGHT, UP, DOWN};

typedef struct Snake {
    PointQueue* body_queue;
    unsigned int size;
    enum Direction direction;
} Snake;

Snake* init_snake(Point, enum Direction);
void free_snake(Snake*);
void snake_move(Snake*);

#endif