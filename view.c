// #include <curses.h>
// #include "snake.h"
#include "view.h"

void draw_snake(WINDOW *window, Snake *snake)
{
    for (int i = 0; i < snake->length; i++)
    {
        Node *node = snake->body[i];
        mvwprintw(window, node->y, node->x, "%c", node->symbol);
    }
}

void draw_food(WINDOW *window, Food *food)
{
    mvwprintw(window, food->y, food->x, "%c", food->symbol);
}

void draw_border(WINDOW *window)
{
    wborder(window, '|', '|', '-', '-', '+', '+', '+', '+');
}