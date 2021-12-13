#include <stdlib.h>
#include "display.h"

DisplayWindow* init_display(unsigned short width, unsigned short height) {
    DisplayWindow* display = (DisplayWindow*)malloc(sizeof(DisplayWindow));
    display->width = width;
    display->height = height;

    return display;
}

void free_display(DisplayWindow* display) {
    free(display);
}

void display_set_cell(DisplayWindow* display, unsigned short x, unsigned short y, const char c) {
    gotoxy(x, y);
    putchar(c);
    gotoxy(0, 0);
}

