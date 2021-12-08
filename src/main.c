#include <stdio.h>
#include <stdlib.h>
#include "grid.h"

#define MAX_ROW 32
#define MAX_COL 32

int main() {
    srand(time(NULL));
    printf("Hello World!\n");

    Grid* grid = init_grid(MAX_ROW, MAX_COL);

    return 0;
}