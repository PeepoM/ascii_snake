#include <curses.h>
#include "snake.h"

void draw_snake(WINDOW *window, Snake *snake);

void draw_food(WINDOW *window, Food *food);

void draw_border(WINDOW *window);