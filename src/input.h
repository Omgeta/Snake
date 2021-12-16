#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <pthread.h>
#include <termios.h>
#include <unistd.h>

void init_input();
void destroy_input();
int input_read();

#endif