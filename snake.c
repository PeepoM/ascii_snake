#include <stdlib.h>
#include "snake.h"

Snake *create_snake()
{
    Snake *snake = malloc(sizeof(Snake));

    snake->head = malloc(sizeof(Node));
    snake->head->x = START_X;
    snake->head->y = START_Y;
    snake->head->symbol = HEAD_SYMBOL;

    snake->last_tail_loc = malloc(sizeof(Node));
    *snake->last_tail_loc = *snake->head;

    snake->body[0] = snake->head;
    snake->length = 1;
    snake->dir_x = 0;
    snake->dir_y = 0;

    return snake;
}

void rand_food_loc(Food *food, int width, int height)
{
    food->x = rand() % (width - 2) + 1;
    food->y = rand() % (height - 2) + 1;
}

Food *create_food(int width, int height)
{
    Food *food = malloc(sizeof(Food));

    rand_food_loc(food, width, height);
    food->symbol = FOOD_SYMBOL;

    return food;
}

void check_bounds(Snake *snake, int width, int height)
{
    Node *head = snake->head;

    // check horizontal bounds
    if (head->x < 0)
        head->x = width - 1;
    else if (head->x >= width)
        head->x = 0;

    // check vertical bounds
    if (head->y < 0)
        head->y = height - 1;
    else if (head->y >= height)
        head->y = 0;
}

void check_self_collision(Snake *snake)
{
    Node *head = snake->head;

    for (int i = 1; i < snake->length; i++)
    {
        Node *curr = snake->body[i];

        // check collision point
        if ((head->x == curr->x) && (head->y == curr->y))
        {
            // remove all the nodes coming after (and including) collision node
            for (int j = i; j < snake->length; j++)
            {
                Node *body_node = snake->body[j];
                free(body_node);
            }
            // modify snake length
            snake->length = i;

            return;
        }
    }
}

int is_food_collision(Snake *snake, Food *food)
{
    Node *head = snake->head;
    return (head->x == food->x) && (head->y == food->y);
}

void grow_snake(Snake *snake)
{
    snake->length++;

    // allocate memory for new node
    Node *new_tail = malloc(sizeof(Node));

    // copy contents of one pointer to another
    *new_tail = *snake->last_tail_loc;
    new_tail->symbol = TAIL_SYMBOL;
    snake->body[snake->length - 1] = new_tail;
}

void move_snake(Snake *snake)
{
    Node *head = snake->head;

    // save the last location of the tail -> important for snake growth
    *snake->last_tail_loc = *snake->body[snake->length - 1];

    // move the rest of the body
    for (int i = snake->length - 1; i >= 1; i--)
    {
        Node *curr = snake->body[i];
        Node *prev = snake->body[i - 1];

        curr->x = prev->x;
        curr->y = prev->y;
    }

    // move head
    head->x += snake->dir_x;
    head->y += snake->dir_y;
}