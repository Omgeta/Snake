/*
Output handler
Author: Omgeta
Date: 10/12/2021
*/
#include "output.h"

OutputWindow* init_output(uint8_t width, uint8_t height) {
    OutputWindow* output = (OutputWindow*)malloc(sizeof(OutputWindow));
    output->width = width;
    output->height = height;

    return output;
}

void free_output(OutputWindow* output) {
    free(output);
}

void output_draw_border(OutputWindow* output) {
    // Sides
    for (unsigned int y = 0; y < output->height; y++) {
        _output_set_cell(output, 0, y, BORDER_CELL);
        _output_set_cell(output, output->width-1, y, BORDER_CELL);
    }

    // Top
    for (unsigned int x = 1; x < output->width-1; x++) {
        _output_set_cell(output, x, 0, BORDER_CELL);
    }

    // Bottom
    for (unsigned int x = 1; x < output->width-1; x++) {
        _output_set_cell(output, x, output->height-1, BORDER_CELL);
    }
}

void output_draw_grid_cell(OutputWindow* output, uint8_t x, uint8_t y, const char c) {
    _output_set_cell(output, x+1, y+1, c); // pad by border size = 1
}

static int _output_is_valid(OutputWindow* output, uint8_t x, uint8_t y) {
    return (x >=0 && x < output->width) &&
            (y >=0 && y < output->height);
}

static void _output_set_cell(OutputWindow* output, uint8_t x, uint8_t y, const char c) {
    if (_output_is_valid(output, x, y)) {
        gotoxy(1+x, 1+y); // add required coordinates to 1, 1 which is the top left
        putchar(c);
        gotoxy(1, 1);
        fflush(stdout);
    }
}


