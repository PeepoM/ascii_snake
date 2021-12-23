#define MAX_LEN 150
#define START_X 5
#define START_Y 5
#define HEAD_SYMBOL 'O'
#define TAIL_SYMBOL 'o'
#define FOOD_SYMBOL '#'

typedef struct
{
    int x, y;
    char symbol;
} Entity;

typedef Entity Node, Food;

typedef struct
{
    Node *head;
    Node *body[MAX_LEN];
    Node *last_tail_loc;

    int length;
    int dir_x, dir_y;
} Snake;

Snake *create_snake();

Food *create_food(int width, int height);

int is_food_collision(Snake *snake, Food *food);

void rand_food_loc(Food *food, int width, int height);

void check_bounds(Snake *snake, int width, int height);

void check_self_collision(Snake *snake);

void grow_snake(Snake *snake);

void move_snake(Snake *snake);