#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "snake.h"
#include "grid.h"
#include "input.h"
#include "output.h"

#define MAX_ROW 32
#define MAX_COL 32
#define UPDATE_DELAY_MS 100000

int update(Grid*, OutputWindow*);
void print_grid(OutputWindow*, Grid*);

int main() {
    // Current time as seed
    srand(time(0));

    // Init
    Grid* grid = init_grid(MAX_ROW, MAX_COL);
    OutputWindow* output = init_output(grid->row_size+2, grid->col_size+2);
    print_grid(output, grid);
    init_input();

    // Update Loop
    int dead = 0;
    while (!dead) {
        dead = update(grid, output);
        usleep(UPDATE_DELAY_MS);
    }

    // Score
    gotoxy(0, output->height+1);
    printf("Score: %d\n", grid->snake->size - 2);

    // Terminate
    free_grid(grid);
    free_output(output);
    destroy_input();

    // Exit
    return 0;
    
}

int update(Grid* grid, OutputWindow* output) {
    // Turn snake based on latest input
    {
        enum Direction dir = input_read();
        if (dir != -1) {
            snake_turn(grid->snake, dir);
        }
    }

    // Move snake
    {
        // Store old points
        Point old_snake_head = grid->snake->body->tail->point;
        Point old_snake_tail = grid->snake->body->head->point;

        // Add new head when moving
        Point new_head = snake_new_head(grid->snake->body, grid->snake->direction);
        queue_enqueue(grid->snake->body, new_head);

        // Check if snake collided with food and increase size if so
        int eaten = snake_collides_food(grid->snake, grid->food);
        if (eaten) {
            grid->food = grid_spawn_food(grid);
            Point food = grid->food;
            output_draw_grid_cell(output, food.x, food.y, FOOD_CELL);
        } else {
            queue_dequeue(grid->snake->body);
            output_draw_grid_cell(output, old_snake_tail.x, old_snake_tail.y, EMPTY_CELL);
        }

        // Handle snake death
        {
            int ate_itself = snake_collides_self(grid->snake);
            int out_of_bounds = !grid_contains_snake(grid);
            if (ate_itself || out_of_bounds) {
                PointNode* curr = grid->snake->body->head;
                while (curr->next != NULL) {
                    Point curr_p = curr->point;
                    output_draw_grid_cell(output, curr_p.x, curr_p.y, SNAKE_DEAD_CELL);
                    curr = curr->next;
                }
                return 1; // exit code
            }
        }

        // Draw cells of snake
        Point snake_head = grid->snake->body->tail->point;
        output_draw_grid_cell(output, snake_head.x, snake_head.y, SNAKE_HEAD_CELL);
        output_draw_grid_cell(output, old_snake_head.x, old_snake_head.y, SNAKE_BODY_CELL);
    }
}

void print_grid(OutputWindow* output, Grid* grid) {
    clear();

    // Add border
    output_draw_border(output);

    // Print out food
    {
        Point food = grid->food;
        output_draw_grid_cell(output, food.x, food.y, FOOD_CELL);
    }

    // Print out snake body and head
    PointNode* curr = grid->snake->body->head;
    while (curr->next != NULL) {
        Point curr_p = curr->point;
        output_draw_grid_cell(output, curr_p.x, curr_p.y, SNAKE_BODY_CELL);
        curr = curr->next;
    }
    {
        Point head_p = curr->point;
        output_draw_grid_cell(output, head_p.x, head_p.y, SNAKE_HEAD_CELL);
    }
}