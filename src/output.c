/*
Output
Author: Omgeta
Date: 10/12/2021
*/
#include "output.h"

OutputWindow* init_output(unsigned short width, unsigned short height) {
    OutputWindow* output = (OutputWindow*)malloc(sizeof(OutputWindow));
    output->width = width;
    output->height = height;

    return output;
}

void free_output(OutputWindow* output) {
    free(output);
}

void output_set_cell(OutputWindow* output, unsigned short x, unsigned short y, const char c) {
    gotoxy(x, y);
    putchar(c);
    gotoxy(0, 0);
    fflush(stdout);
}

