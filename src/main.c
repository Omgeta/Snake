#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "snake.h"
#include "grid.h"
#include "display.h"

#define MAX_ROW 32
#define MAX_COL 32
#define UPDATE_DELAY_S 1

int update(Grid*, DisplayWindow*);
void print_grid(DisplayWindow*, Grid*);

int main() {
    // Random seed
    srand(time(NULL));

    // Init
    Grid* grid = init_grid(MAX_ROW, MAX_COL);
    DisplayWindow* display = init_display(grid->row_size, grid->col_size);
    print_grid(display, grid);

    // Game loop
    int dead = 0;
    while (!dead) {
        // TODO: input
        dead = update(grid, display);
        sleep(UPDATE_DELAY_S);
    }

    // Print score
    clear();
    printf("Score: %d\n", grid->snake->size - 2);

    // Dealloc
    free_grid(grid);
    free_display(display);

    // Exit
    sleep(5);
    return 0;
}

int update(Grid* grid, DisplayWindow* display) {
    // Check if snake collided with food and increase size if so
    int eaten = snake_collides_food(grid->snake, grid->food);
    if (eaten) {
        grid->snake->size++;
        grid_spawn_food(grid);
        Point food = grid->food;
        display_set_cell(display, food.x, food.y, DISPLAY_FOOD_CELL);
    }

    // Move snake
    // Shift head char to new head position
    // Remove tail char if the snake has not grown
    {
        Point old_snake_head = grid->snake->body_queue->tail->point;
        snake_move(grid->snake);
        Point snake_head = grid->snake->body_queue->tail->point;
        display_set_cell(display, snake_head.x, snake_head.y, DISPLAY_SNAKE_HEAD_CELL);
        display_set_cell(display, old_snake_head.x, old_snake_head.y, DISPLAY_SNAKE_BODY_CELL);
        if (!eaten) {
            Point snake_tail = grid->snake->body_queue->head->point;
            display_set_cell(display, snake_tail.x, snake_tail.y, DISPLAY_EMPTY_CELL);
        }
    }

    // End game if snake went out of bounds or ate itself
    int died = snake_collides_self(grid->snake) || !grid_contains_snake(grid);
    if (died) {
        PointNode* curr = grid->snake->body_queue->head;
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
    PointNode* curr = grid->snake->body_queue->head;
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