#ifndef POINT_H
#define POINT_H

typedef struct Point2D {
    unsigned short int x;
    unsigned short int y;
} Point;

typedef struct PointNode PointNode;
struct PointNode {
    Point point;
    PointNode* next;
};

typedef struct PointQueue {
    PointNode* head;
    PointNode* tail;
} PointQueue;

int point_eq(Point, Point);
PointQueue* init_queue(void);
void free_queue(PointQueue*);
void queue_enqueue(PointQueue*, Point);
Point queue_dequeue(PointQueue*);
int queue_includes(PointQueue*, Point);
Point queue_get(PointQueue*, unsigned int);
unsigned int queue_size(PointQueue*);

#endif