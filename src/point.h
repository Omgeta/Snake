#ifndef POINT_H
#define POINT_H

typedef struct Point2D {
    unsigned short x;
    unsigned short y;
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
Point queue_dequeue(PointQueue*);
int queue_includes(PointQueue*, Point);
Point queue_get(PointQueue*, unsigned int);
unsigned int queue_size(PointQueue*);

#endif