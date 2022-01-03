#include <stdlib.h>
#include <time.h>
#include "snake.h"
#include "view.h"

#define DELAY 50

typedef enum
{
    KEY_A = 97,
    KEY_D = 100,
    KEY_S = 115,
    KEY_W = 119
} KEY;

void process_input(KEY key, Snake *snake);

int main()
{
    initscr(); // initialize curses

    srand(time(NULL)); // setup seed for random numbers

    int term_width, term_height;
    int b_width, b_height;

    // get height and width of the terminal window
    getmaxyx(stdscr, term_height, term_width);

    WINDOW *board = newwin(term_height, 2 * term_width / 3, 0, 0);
    getmaxyx(board, b_height, b_width);

    // raw();
    curs_set(FALSE);       // disable cursor
    noecho();              // pressed symbols not printed to the screen
    nodelay(stdscr, TRUE); // getch doesn't wait for user to press Enter
    keypad(stdscr, TRUE);

    Snake *snake = create_snake();
    Food *food = create_food(b_width, b_height);

    while (TRUE)
    {
        werase(board);

        // process input
        KEY key = getch();
        process_input(key, snake);

        // update game state
        move_snake(snake);
        check_self_collision(snake);
        check_bounds(snake, b_width, b_height);

        if (is_food_collision(snake, food))
        {
            grow_snake(snake);
            rand_food_loc(food, b_width, b_height);
        }

        // render screen
        draw_border(board);
        draw_food(board, food);
        draw_snake(board, snake);

        wrefresh(board);

        napms(DELAY);
    }

    endwin();

    return 0;
}

void process_input(KEY key, Snake *snake)
{
    if (key == KEY_A && snake->dir_x != 1)
    {
        snake->dir_x = -1;
        snake->dir_y = 0;
    }
    else if (key == KEY_D && snake->dir_x != -1)
    {
        snake->dir_x = 1;
        snake->dir_y = 0;
    }
    else if (key == KEY_S && snake->dir_y != -1)
    {
        snake->dir_x = 0;
        snake->dir_y = 1;
    }
    else if (key == KEY_W && snake->dir_y != 1)
    {
        snake->dir_x = 0;
        snake->dir_y = -1;
    }
}