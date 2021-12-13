#ifndef INPUT_H
#define INPUT_H
#include <stdio.h>
#include <pthread.h>

pthread_t init_input();
void destroy_input(pthread_t);
int input_read();

#endif