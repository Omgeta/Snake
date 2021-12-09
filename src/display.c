#include <stdlib.h>
#include "display.h"

DisplayWindow* init_display(unsigned short int width, unsigned short int height) {
    DisplayWindow* display = (DisplayWindow*)malloc(sizeof(DisplayWindow));
    display->width = width;
    display->height = height;

    return display;
}

void free_display(DisplayWindow* display) {
    free(display);
}

int display_is_valid(DisplayWindow* display, unsigned short int x, unsigned short int y) {
    return (x >= 0 && x < display->width) &&
            (y >= 0 && y < display->height);
}

void display_set_cell(DisplayWindow* display, unsigned short int x, unsigned short int y, const char c) {
    if (display_is_valid(display, x, y)) {
        gotoxy(x, y);
        putchar(c);
        gotoxy(0, 0);
    }
}

