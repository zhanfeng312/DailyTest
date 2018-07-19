#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#define APPLE          '@'
#define SNAKEHEAD      '+'
#define SNAKETAIL      '-'
#define SIZE           10 
typedef struct {
    int row;
    int col;
} Pos;
typedef struct {
    Pos head;
    Pos tail;
} Snake;

Snake snake;
Pos apple;

bool is_same(const Pos* pFirstPos, const Pos* pSecondPos) {
    if ((pFirstPos->row == pSecondPos->row) && (pFirstPos->col == pSecondPos->col)) {
        return true;
    }
    else {
        return false;
    }
}

void init_snake() {
    int row = rand() % (SIZE - 2);
    int col = rand() % (SIZE - 2);
    int direction = rand() % 4;
    snake.head.row = row;
    snake.head.col = col;
    switch(direction) {
        case 0:
            //尾巴在头上边
            snake.tail.row = row - 1;
            snake.tail.col = col;
            break;
        case 1:
            //尾巴在头下面
            snake.tail.row = row + 1;
            snake.tail.col = col;
            break;
        case 2:
            //尾巴在头左边
            snake.tail.row = row;
            snake.tail.col = col - 1;
            break;
        default:
            //尾巴在头右边
            snake.tail.row = row;
            snake.tail.col = col + 1;
            break;
    }
}

void plant_apple() {
    do {
       apple.row = rand() % (SIZE - 2);
       apple.col = rand() % (SIZE - 2);
    } while ((is_same(&apple, &(snake.head))) || (is_same(&apple, &(snake.tail))));
}

void show_map() {
    int row = 0;
    int col = 0;
    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            if ((row == apple.row) && (col == apple.col)) {
                printf("%c", APPLE);
            }
            else if ((row == snake.head.row) && (col == snake.head.col)) {
                printf("%c", SNAKEHEAD);
            }
            else if ((row == snake.tail.row) && (col == snake.tail.col)) {
                printf("%c", SNAKETAIL);
            }
            else {
                printf(" ");
            }
        }
        printf("\n");
    }
}
void move_snake() {
    int direction = 0;
    int row = 0;
    int col = 0;
    printf("请输入移动的方向：（0表示向上，1表示向左，2表示向下，3表示向右）");
    scanf("%d", &direction);
    switch(direction) {
        case 0:
            if ((snake.head.row - 1) >= 0) {
                snake.tail.row = snake.head.row;
                snake.tail.col = snake.head.col;
                snake.head.row--;
            }
            break;
        case 1:
            if ((snake.head.col - 1) >= 0) {
                snake.tail.row = snake.head.row;
                snake.tail.col = snake.head.col;
                snake.head.col--;
            }
            break;
        case 2:
            if ((snake.head.row + 1) < SIZE){
                snake.tail.row = snake.head.row;
                snake.tail.col = snake.head.col;
                snake.head.row++;
            }
            break;
        default:
            if ((snake.head.col + 1) < SIZE) {
                snake.tail.row = snake.head.row;
                snake.tail.col = snake.head.col;
                snake.head.col++;
            }
            break;
    }
    if (is_same(&apple, &(snake.head)) || (is_same(&apple, &(snake.tail)))) {
        plant_apple();
    }
}
int main() {
    srand(time(0));
    init_snake();
    plant_apple();
    show_map();
    while (1) {  //死循环
        move_snake();
        show_map();
    }
    return 0;
}
