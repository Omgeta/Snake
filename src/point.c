/*
Dynamic Queue of Points in the Grid
Author: Omgeta
Date: 8/12/2021
*/
#include <stdlib.h>
#include "point.h"

int point_eq(Point p1, Point p2) {
    return (p1.x == p2.x) && \
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
    PointNode* new_node = (PointNode*)malloc(sizeof(PointNode));
    new_node->point = point;
    new_node->next = NULL;

    if (point_queue->head == NULL) {
        point_queue->head = new_node;
    } else {
        PointNode* curr = point_queue->head;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = new_node;
    }
    point_queue->tail = new_node;
}

Point queue_dequeue(PointQueue* point_queue) {
    if (point_queue->head != NULL) {
        Point point = point_queue->head->point;
        PointNode* temp_next = point_queue->head->next;
        free(point_queue->head);
        point_queue->head = temp_next;
        return point;
    } else {
        // ADD FAIL CASE
    }
}

int queue_includes(PointQueue* point_queue, Point target) {
    if (point_queue->head == NULL) {
        return 0;
    } else {
        int found = 0;
        PointNode* curr = point_queue->head;
        while (!found && curr != NULL) {
            if (point_eq(curr->point, target)) {
                found = 1;
            }
            curr = curr->next;
        }
        return found;
    }
}

Point queue_get(PointQueue* point_queue, unsigned int i) {
    unsigned int j = 0;
    PointNode* prev = NULL;
    PointNode* curr = point_queue->head;
    while (curr != NULL  && j < i) {
        j++;
        prev = curr;
        curr = curr->next;
    }
    
    if (j == i && (prev != NULL || curr != NULL)) {
        return curr->point;
    } else {
        // ADD FAIL CASE
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