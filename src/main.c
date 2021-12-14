#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "snake.h"
#include "grid.h"
#include "display.h"
#include "input.h"

#define MAX_ROW 16
#define MAX_COL 16
#define UPDATE_DELAY_S 1

int update(Grid*, DisplayWindow*);
void print_grid(DisplayWindow*, Grid*);

void debug(FILE* fptr, Grid* grid) {
    fprintf(fptr, "====\n");
    PointNode* tail = grid->snake->body->head;
    while (tail != NULL) {
        fprintf(fptr, "X:%d Y:%d\n", tail->point.x, tail->point.y);
        tail = tail->next;
    }
}

int main() {
    // Random seed
    srand(time(0));

    // Debug
    FILE* fptr = fopen("/mnt/c/Scripts/Snake/out.txt", "w+");
    if (fptr == NULL) {
        printf("Error");
        exit(1);
    }

    // Init
    Grid* grid = init_grid(MAX_ROW, MAX_COL);
    DisplayWindow* display = init_display(grid->row_size, grid->col_size);
    print_grid(display, grid);
    pthread_t ptid = init_input();

    // Game loop
    int dead = 0;
    while (!dead) {
        debug(fptr, grid);
        dead = update(grid, display);
        sleep(UPDATE_DELAY_S);
    }
    debug(fptr, grid);

    // Print score
    gotoxy(0, display->height+1);
    printf("Score: %d\n", grid->snake->size - 2);

    // Dealloc
    free_grid(grid);
    free_display(display);

    //Debug
    fclose(fptr);

    // Exit
    return 0;
}

int update(Grid* grid, DisplayWindow* display) {
    // Check if snake collided with food and increase size if so
    int eaten = snake_collides_food(grid->snake, grid->food);
    if (eaten) {
        grid->snake->size++;
        grid->food = grid_spawn_food(grid);
        Point food = grid->food;
        display_set_cell(display, food.x, food.y, DISPLAY_FOOD_CELL);
    }

    // Turn snake based on latest input
    {
        enum Direction dir = input_read();
        if (dir != -1) {
            snake_turn(grid->snake, dir);
        }
    }

    // Move snake
    {
        // Shift head char to new head position
        Point old_snake_head = grid->snake->body->tail->point;
        Point old_snake_tail = grid->snake->body->head->point;
        snake_move(grid->snake);
        Point snake_head = grid->snake->body->tail->point;
        display_set_cell(display, snake_head.x, snake_head.y, DISPLAY_SNAKE_HEAD_CELL);
        display_set_cell(display, old_snake_head.x, old_snake_head.y, DISPLAY_SNAKE_BODY_CELL);
        
        // Remove tail char if the snake has not grown
        if (!eaten) {
            display_set_cell(display, old_snake_tail.x, old_snake_tail.y, DISPLAY_EMPTY_CELL);
        }
    }

    // End game if snake went out of bounds or ate itself
    int ate_itself = snake_collides_self(grid->snake);
    int out_of_bounds = !grid_contains_snake(grid);
    if (ate_itself || out_of_bounds) {
        PointNode* curr = grid->snake->body->head;
        while (curr != NULL) {
            Point curr_p = curr->point;
            display_set_cell(display, curr_p.x, curr_p.y, DISPLAY_SNAKE_DEAD_CELL);
            curr = curr->next;
        }

        return 1; // exit code
    }
}

void print_grid(DisplayWindow* display, Grid* grid) {
    clear();
    // Print out food
    {
        Point food = grid->food;
        display_set_cell(display, food.x, food.y, DISPLAY_FOOD_CELL);
    }

    // Print out snake body and head
    PointNode* curr = grid->snake->body->head;
    while (curr->next != NULL) {
        Point curr_p = curr->point;
        display_set_cell(display, curr_p.x, curr_p.y, DISPLAY_SNAKE_BODY_CELL);
        curr = curr->next;
    }
    {
        Point head_p = curr->point;
        display_set_cell(display, head_p.x, head_p.y, DISPLAY_SNAKE_HEAD_CELL);
    }
}