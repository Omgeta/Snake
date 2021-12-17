#ifndef POINT_H
#define POINT_H

#include <stdint.h>

typedef struct Point2D {
    uint8_t x;
    uint8_t y;
} Point;

int point_eq(Point, Point);

typedef struct PointNode PointNode;
struct PointNode {
    Point point;
    PointNode* next;
};

typedef struct PointQueue {
    PointNode* head;
    PointNode* tail;
} PointQueue;

PointQueue* init_queue(void);
void free_queue(PointQueue*);
void queue_enqueue(PointQueue*, Point);
void queue_dequeue(PointQueue*);
uint8_t queue_size(PointQueue*);

#endif