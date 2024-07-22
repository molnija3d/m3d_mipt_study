#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>
#include <inttypes.h>
#include <string.h>
#include <unistd.h>

#define MIN_Y  2
enum {
    LEFT = 1,
    UP,
    RIGHT,
    DOWN,
    STOP_GAME = KEY_F( 10 ),
    GAME_OVER = 99,
    VICTORY = 100
};

enum {
    MAX_TAIL_SIZE = 100,
    START_TAIL_SIZE = 3,
    MAX_FOOD_SIZE = 20,
    FOOD_EXPIRE_SECONDS = 10,
    SEED_NUMBER = 3,
    VIC_COUNT = 20 
};


// Здесь храним коды управления змейкой
typedef struct control_buttons {
    int down;
    int up;
    int left;
    int right;
} control_buttons;

control_buttons default_controls[3] = {
    {KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT},
    {'s', 'w', 'a', 'd'},
    {'S', 'W', 'A', 'D'}
};

/*
 Голова змейки содержит в себе
 x,y - координаты текущей позиции
 direction - направление движения
 tsize - размер хвоста
 *tail -  ссылка на хвост
 */
typedef struct snake_t {
    int x;
    int y;
    int direction;
    size_t tsize;
    struct tail_t *tail;
//    struct control_buttons controls;
} snake_t;

/*
 Хвост это массив состоящий из координат x,y
 */
typedef struct tail_t {
    int x;
    int y;
} tail_t;
/*
 Еда — это массив точек, состоящий из координат x,y, времени,
 когда данная точка была установлена, и поля, сигнализирующего,
 была ли данная точка съедена.
 */
struct food {
    int x;
    int y;
    time_t put_time;
    char point;
    uint8_t enable;
} food[ MAX_FOOD_SIZE ];

void initFood(struct food f[], size_t size) {
    struct food init = {0, 0, 0, 0, 0};
    for(size_t i = 0; i < size; i++) {
        f[i] = init;
    }
}
/*
 Обновить/разместить текущее зерно на поле
 */
void putFoodSeed(struct food *fp) {
    int max_x = 0, max_y = 0;
    char spoint[2] = {0};
    getmaxyx(stdscr, max_y, max_x);
    mvprintw(fp -> y, fp -> x, " ");
    fp -> x = rand() % (max_x - 1);
    fp -> y = rand() % (max_y - 2) + 1; //Не занимаем верхнюю строку
    fp -> put_time = time(NULL);
    fp -> point = '$';
    fp -> enable = 1;
    spoint[0] = fp -> point;
    mvprintw(fp -> y, fp -> x, "%s", spoint);
}

/*
 Разместить еду на поле
 */
void putFood(struct food f[], size_t number_seeds) {
    for(size_t i = 0; i < number_seeds; i++) {
        putFoodSeed( &f[i] );
    }
}

void refreshFood(struct food f[], int nfood) {
    for(size_t i = 0; i < nfood; i++) {
        if( f[i].put_time ) {
            if( !f[i].enable || (time(NULL) - f[i].put_time) > FOOD_EXPIRE_SECONDS ) {
                putFoodSeed( &f[i] );
            }
        }
    }
}
void initTail(tail_t t[], size_t size) {
    struct tail_t init_t = {0, 0};
    for(size_t i = 0; i < size; i++) {
        t[i] = init_t;
    }
}
void initHead(snake_t *head, int x, int y) {
    head -> x = x;
    head -> y = y;
    head -> direction = RIGHT;
}

void initSnake(snake_t *head, size_t size, int x, int y) {
    tail_t *tail  = ( tail_t* ) malloc( MAX_TAIL_SIZE * sizeof( tail_t ) );
    initTail( tail, MAX_TAIL_SIZE );
    initHead( head, x, y );
    head -> tail = tail; // прикрепляем к голове хвост
    head -> tsize = size + 1;
    // head -> controls = default_controls;
}

/*
 Движение головы с учетом текущего направления движения
 */
void go(snake_t *head) {
    char ch = '@';
    int max_x = 0, max_y = 0;
    getmaxyx(stdscr, max_y, max_x); // macro - размер терминала
    mvprintw(head -> y, head -> x, " "); // очищаем один символ
    switch (head -> direction) {
    case LEFT:
        if(head -> x <=  0) // Циклическое движение, чтобы не
// уходить за пределы экрана
            head -> x = max_x;
        mvprintw(head -> y, --(head -> x), "%c", ch);
        break;
    case RIGHT:
        if(head -> x >= max_x) {
            head -> x = 0;
        }
        mvprintw(head -> y, ++(head -> x), "%c", ch);
        break;
    case UP:
        if(head -> y <= 1) {
            head -> y = max_y;
        }
        mvprintw(--(head -> y), head -> x, "%c", ch);
        break;
    case DOWN:
        if(head -> y >= max_y) {
            head -> y = 0;
        }
        mvprintw(++(head -> y), head -> x, "%c", ch);
        break;
    default:
        break;
    }
    refresh();
}

void changeDirection(snake_t *snake, const int32_t key) {
    for(uint8_t i = 0; i < 3; i++) {
        if (key ==  default_controls[i].down) {
            if(snake -> direction != UP)
                snake -> direction = DOWN;
        }
        else if (key ==  default_controls[i].up) {
            if(snake -> direction != DOWN)
                snake -> direction = UP;
        }
        else if (key ==  default_controls[i].right) {
            if(snake -> direction != LEFT)
                snake -> direction = RIGHT;
        }

        else if (key ==  default_controls[i].left) {
            if(snake -> direction != RIGHT)
                snake -> direction = LEFT;
        }

    }
}

/*
 Движение хвоста с учетом движения головы
 */
void goTail(snake_t *head) {
    char ch = '*';
    mvprintw(head -> tail[head -> tsize-1].y, head -> tail[head -> tsize-1].x, " ");
    for(size_t i = head -> tsize-1; i>0; i--) {
        head -> tail[i] = head -> tail[i-1];
        if( head -> tail[i].y || head -> tail[i].x)
            mvprintw(head -> tail[i].y, head -> tail[i].x, "%c", ch);
    }
    head -> tail[0].x = head -> x;
    head -> tail[0].y = head -> y;
}

void addTail(snake_t *head) {
    head -> tsize++;
}

void haveEat(snake_t *head, struct food f[]) {
    for(size_t i = 0; i < MAX_FOOD_SIZE; i++) {
        if(f[i].x == head -> x && f[i].y == head -> y) {
            addTail(head);
        }
    }
}

int checkCoords(snake_t *head)
{
    int res = 0;
    for(size_t i = 1; i < head -> tsize; i++) {
        if(head -> x == head -> tail[i].x && head -> y == head -> tail[i].y) {
            res = GAME_OVER;
        }
    }
    if(head -> tsize >= VIC_COUNT && res != GAME_OVER) {
        res = VICTORY;
    }
    return res;
}

void end_game(int res) {
    int max_x = 0, max_y = 0;
    getmaxyx(stdscr, max_y, max_x);
    switch(res) {
    case GAME_OVER:
        mvprintw(max_y / 2, max_x / 2, "GAME OVER");
        while(getch() != STOP_GAME);
        break;
    case VICTORY:
        mvprintw(max_y / 2, max_x / 2, "VICTORY");
        while(getch() != STOP_GAME);
        break;
    }

}

int main()
{
    snake_t *snake = ( snake_t* ) malloc( sizeof( snake_t ) );
    initSnake( snake, START_TAIL_SIZE, 10, 10 );
    initscr();
    keypad(stdscr, TRUE); // Включаем F1, F2, стрелки и т.д.
    raw();                // Откдючаем line buffering
    noecho();            // Отключаем echo() режим при вызове getch
    curs_set(FALSE);    //Отключаем курсор
    mvprintw(0, 5, "Use arrows or WSAD for control. Eat %d '$' for VICTORY! Press 'F10' for EXIT", VIC_COUNT);
    timeout(0);    //Отключаем таймаут после нажатия клавиши в цикле
    initFood(food, MAX_FOOD_SIZE);
    putFood(food, SEED_NUMBER);// Кладем зерна
    int key_pressed = 0;
    int res = 0;
    while( key_pressed !=  STOP_GAME && res != GAME_OVER && res != VICTORY) {
        key_pressed = getch(); // Считываем клавишу
        go(snake);
        goTail(snake);
        haveEat(snake, food);
        res = checkCoords(snake);
        timeout(100);
        refreshFood(food, SEED_NUMBER);// Обновляем еду
        changeDirection(snake, key_pressed);
    }

    end_game(res);
    free(snake -> tail);
    free(snake);
    endwin(); // Завершаем режим curses mod
    return 0;
}
