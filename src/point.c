/*
Dynamically allocated queue of 2D Points
Author: Omgeta
Date: 8/12/2021
*/
#include "point.h"

int point_eq(Point p1, Point p2) {
    return (p1.x == p2.x) &&
            (p1.y == p2.y);
}

PointQueue* init_queue() {
    PointQueue* point_queue = (PointQueue*)malloc(sizeof(PointQueue));
    point_queue->head = NULL;
    return point_queue;
}

void free_queue(PointQueue* point_queue) {
    PointNode* prev = NULL;
    PointNode* curr = point_queue->head;
    while (curr != NULL) {
        prev = curr;
        curr = curr->next;
        free(prev);
    }

    free(point_queue);
}

void queue_enqueue(PointQueue* point_queue, Point point) {
    // Create new node to add
    PointNode* new_node = (PointNode*)malloc(sizeof(PointNode));
    new_node->point = point;
    new_node->next = NULL;

    if (point_queue->head == NULL) {
        // Special case: set new node as head when there is no current head
        point_queue->head = new_node;
    } else {
        // Add new node to the end of the current queue
        PointNode* curr = point_queue->head;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = new_node;
    }

    // Tail always refers to the newest enqueued node
    point_queue->tail = new_node;
}

void queue_dequeue(PointQueue* point_queue) {
    if (point_queue->head != NULL) {
        // Pop head node
        Point point = point_queue->head->point;
        PointNode* temp_next = point_queue->head->next;
        free(point_queue->head);

        // Point head to the next remaining node
        point_queue->head = temp_next;
    }
}

unsigned int queue_size(PointQueue* point_queue) {
    unsigned int i = 0;
    PointNode* curr = point_queue->head;
    while (curr != NULL) {
        i++;
        curr = curr->next;
    }
    return i;
}