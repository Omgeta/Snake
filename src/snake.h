#ifndef SNAKE_H
#define SNAKE_H

#include "point.h"

enum Direction {LEFT, RIGHT, UP, DOWN};

typedef struct Snake {
    PointQueue* body;
    unsigned int size;
    enum Direction direction;
} Snake;

Snake* init_snake(Point, enum Direction);
void free_snake(Snake*);
void snake_turn(Snake*, enum Direction);
int snake_collides_food(Snake*, Point);
int snake_collides_self(Snake*);
Point snake_new_head(PointQueue*, enum Direction);
static PointQueue* _init_snake_body(Point, enum Direction, unsigned short);
static int _snake_same_or_opp_dir(enum Direction dir1, enum Direction dir2);

#endif