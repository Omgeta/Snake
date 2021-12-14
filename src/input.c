/*
Input
Author: Omgeta
Date: 12/12/2021
*/
#include "input.h"

char input_buf = 0;

void* thread_input(void* vargp) {
    for (;;) {
        int c = getchar();
        if (c != '\n') {
            input_buf = c;
        }
    } 
}

pthread_t init_input() {
    pthread_t ptid; 
    pthread_create(&ptid, NULL, thread_input, NULL);
    return ptid;
}

void destroy_input(pthread_t ptid) {
    pthread_join(ptid, NULL);
}

int input_read() {
    int out; // DOWN = 0, RIGHT = 1, UP = 2, DOWN = 3
    switch (input_buf) {
        case 'A':
        case 'a':
            out = 0;
            break;
        case 'D':
        case 'd':
            out = 1;
            break;
        case 'W':
        case 'w':
            out = 2;
            break;
        case 'S':
        case 's':
            out = 3;
            break;
        default:
            out = -1;
            break;
    }
    input_buf = 0;
    return out;
}



