#ifndef SNAKE_H
#define SNAKE_H

#include <stdint.h>
#include "point.h"

enum Direction {
    LEFT,   // 0
    RIGHT,  // 1
    UP,     // 2
    DOWN    // 3
};

typedef struct Snake {
    PointQueue* body;
    enum Direction direction;
} Snake;

Snake* init_snake(Point, enum Direction);
void free_snake(Snake*);
uint8_t snake_length(Snake*);
void snake_turn(Snake*, enum Direction);
void snake_add_head(Snake*);
void snake_remove_tail(Snake*);
int snake_collides_food(Snake*, Point);
int snake_collides_self(Snake*);
static PointQueue* _init_snake_body(Point, enum Direction, uint8_t);
static Point _snake_next_head(PointQueue*, enum Direction);
static int _snake_same_or_opp_dir(enum Direction dir1, enum Direction dir2);

#endif