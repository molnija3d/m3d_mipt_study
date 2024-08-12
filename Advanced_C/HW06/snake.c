#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <inttypes.h>
#include <string.h>
#include <unistd.h>
#include <panel.h>

#define MIN_Y 2
#define MAX_PLAYERS 2;
int8_t PLAYERS = 2;

enum {
    LEFT = 1,
    UP,
    RIGHT,
    DOWN,
    STOP_GAME = KEY_F( 10 ),
    GAME_OVER = 99,
    VICTORY = 100,
    PLR_1_WIN = 101,
    PLR_2_WIN = 102,
    PLR_AI_WN = 111
};

enum {
    HEAD = '@',
    TAIL = '*',
    FOOD = '$'
};

enum {
    MAX_TAIL_SIZE = 100,
    START_TAIL_SIZE = 3,
    MAX_FOOD_SIZE = 20,
    FOOD_EXPIRE_SECONDS = 10,
    SEED_NUMBER = 3,
    VIC_COUNT = 10,
    CONTROLS = 2
};


// Здесь храним коды управления змейкой
typedef struct {
    int down;
    int up;
    int left;
    int right;
} control_buttons;

control_buttons default_controls[CONTROLS] = {
    {KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT},
    {'s', 'w', 'a', 'd'},
};

/*
 Хвост это массив состоящий из координат x,y
 */
typedef struct {
    int x;
    int y;
} tail_t;

/*
 Голова змейки содержит в себе
 x,y - координаты текущей позиции
 direction - направление движения
 tsize - размер хвоста
 *tail -  ссылка на хвост
 */
typedef struct {
    int x;
    int y;
    int direction;
    size_t tsize;
    tail_t *tail;

//    struct control_buttons controls;
} snake_t;

/*
 Еда — это массив точек, состоящий из координат x,y, времени,
 когда данная точка была установлена, и поля, сигнализирующего,
 была ли данная точка съедена.
 */
typedef struct {
    int x;
    int y;
    time_t put_time;
    char point;
    uint8_t enable;
} food_t;

void initFood(food_t f[], size_t size) {
    food_t init = {0, 0, 0, 0, 0};
    for(size_t i = 0; i < size; i++) {
        f[i] = init;
    }
}

// Работа с цветом
//
void setColor(int objectType) {
    attroff(COLOR_PAIR(1));
    attroff(COLOR_PAIR(2));
    attroff(COLOR_PAIR(3));
    attroff(COLOR_PAIR(4));

    switch (objectType) {
    case 1: { //SNAKE1
        attron(COLOR_PAIR(1));
        break;
    }
    case 2: { // SNAKE2
        attron(COLOR_PAIR(2));
        break;
    }
    case 3: { // FOOD
        attron(COLOR_PAIR(3));
        break;
    }
    default:
        attron(COLOR_PAIR(1));
    }

}

/*
 Обновить/разместить текущее зерно на поле
 */
void putFoodSeed(food_t *fp) {
    int max_x = 0, max_y = 0;
    char spoint[2] = {0};
    setColor(3);
    getmaxyx(stdscr, max_y, max_x);
    mvprintw(fp -> y, fp -> x, " ");
    fp -> x = rand() % (max_x - 1);
    fp -> y = rand() % (max_y - 2) + 1; //Не занимаем верхнюю строку
    fp -> put_time = time(NULL);
    fp -> point = FOOD;
    fp -> enable = 1;
    spoint[0] = fp -> point;
    mvprintw(fp -> y, fp -> x, "%s", spoint);
}

/*
 Разместить еду на поле
 */
void putFood(food_t f[], size_t number_seeds) {
    for(size_t i = 0; i < number_seeds; i++) {
        putFoodSeed( &f[i] );
    }
}

void refreshFood(food_t f[], int nfood) {
    for(size_t i = 0; i < nfood; i++) {
        if( f[i].put_time ) {
            if( !f[i].enable || (time(NULL) - f[i].put_time) > FOOD_EXPIRE_SECONDS ) {
                putFoodSeed( &f[i] );
            }
        }
    }
}
void initTail(tail_t t[], size_t size) {
    tail_t init_t = {0, 0};
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
    int max_x = 0, max_y = 0;
    getmaxyx(stdscr, max_y, max_x); // macro - размер терминала
    mvprintw(head -> y, head -> x, " "); // очищаем один символ
    switch (head -> direction) {
    case LEFT:
        if(head -> x <=  0) // Циклическое движение, чтобы не
// уходить за пределы экрана
            head -> x = max_x;
        mvprintw(head -> y, --(head -> x), "%c", HEAD);
        break;
    case RIGHT:
        if(head -> x >= max_x) {
            head -> x = 0;
        }
        mvprintw(head -> y, ++(head -> x), "%c", HEAD);
        break;
    case UP:
        if(head -> y <= 1) {
            head -> y = max_y;
        }
        mvprintw(--(head -> y), head -> x, "%c", HEAD);
        break;
    case DOWN:
        if(head -> y >= max_y) {
            head -> y = 0;
        }
        mvprintw(++(head -> y), head -> x, "%c", HEAD);
        break;
    default:
        break;
    }
    refresh();
}

int checkDirection(snake_t* snake, int32_t key, uint8_t player) {
    int res = 0;
    if (key ==  default_controls[player].down) {
        if(snake -> direction != UP)
            res = 1;
    }
    else if (key ==  default_controls[player].up) {
        if(snake -> direction != DOWN)
            res = 1;
    }
    else if (key ==  default_controls[player].right) {
        if(snake -> direction != LEFT)
            res = 1;
    }

    else if (key ==  default_controls[player].left) {
        if(snake -> direction != RIGHT)
            res = 1;
    }

    return res;
}
void changeDirection(snake_t *snake, const int32_t key, uint8_t player) {
    if(checkDirection(snake, key, player)) {
        if (key ==  default_controls[player].down) {
            snake -> direction = DOWN;
        }
        else if (key ==  default_controls[player].up) {
            snake -> direction = UP;
        }
        else if (key ==  default_controls[player].right) {
            snake -> direction = RIGHT;
        }

        else if (key ==  default_controls[player].left) {
            snake -> direction = LEFT;
        }

    }
}

/*
 Движение хвоста с учетом движения головы
 */
void goTail(snake_t *head) {
    mvprintw(head -> tail[head -> tsize - 1].y, head -> tail[head -> tsize - 1].x, " ");
    for(size_t i = head -> tsize - 1; i > 0; i--) {
        head -> tail[i] = head -> tail[ i - 1 ];
        if( head -> tail[i].y || head -> tail[i].x)
            mvprintw(head -> tail[i].y, head -> tail[i].x, "%c", TAIL);
    }
    head -> tail[0].x = head -> x;
    head -> tail[0].y = head -> y;
}

void addTail(snake_t *head) {
    ++(head -> tsize);
}

void haveEat(snake_t *head, food_t f[]) {
    for(size_t i = 0; i < MAX_FOOD_SIZE; i++) {
        if(f[i].x == head -> x && f[i].y == head -> y) {
            addTail(head);
        }
    }
}

int checkSelfCross(snake_t *head)
{
    int res = 0;
    for(size_t i = 1; i < head -> tsize; i++) {
        if(head -> x == head -> tail[i].x && head -> y == head -> tail[i].y) {
            res = GAME_OVER;
            break;
        }
    }
    if(head -> tsize > VIC_COUNT + START_TAIL_SIZE && res != GAME_OVER) {
        res = VICTORY;
    }
    return res;
}

void end_game(int res) {
    int max_x = 0, max_y = 0;
    getmaxyx(stdscr, max_y, max_x);
    attroff(COLOR_PAIR(1));
    attroff(COLOR_PAIR(2));
    attroff(COLOR_PAIR(3));
    attroff(COLOR_PAIR(4));
    switch(res) {
    case GAME_OVER:
        attron(COLOR_PAIR(4));
        mvprintw(max_y / 2, max_x / 2, "GAME OVER");
        while(getch() != STOP_GAME);
        break;
    case VICTORY:
        attron(COLOR_PAIR(4));
        mvprintw(max_y / 2, max_x / 2, "VICTORY");
        while(getch() != STOP_GAME);
        break;
    case PLR_1_WIN:
        attron(COLOR_PAIR(1));
        mvprintw(max_y / 2, max_x / 2, "PLAYER 1 WIN");
        while(getch() != STOP_GAME);
        break;
    case PLR_2_WIN:
        attron(COLOR_PAIR(2));
        mvprintw(max_y / 2, max_x / 2, "PLAYER 2 WIN");
        while(getch() != STOP_GAME);
        break;
    }

}
int lwr_case(int key_pressed) {
    int res = 0;
    switch(key_pressed) {
    case 'W':
        res = 'w';
        break;
    case 'S':
        res = 's';
        break;
    case 'A':
        res = 'a';
        break;
    case 'D':
        res = 'd';
        break;
    }
    return res > 0 ? res: key_pressed;
}

int32_t update(snake_t *head, food_t *food) {
    int key_pressed = 0;
    int res = 0;
    while( key_pressed !=  STOP_GAME && !res ) {
        key_pressed = getch(); // Считываем клавишу
        key_pressed = lwr_case(key_pressed);		       //
        //
        for(uint8_t i = 0; i < PLAYERS && !res; i++) {
            setColor(i + 1);
            go(&head[ i ]);
            goTail(&head[ i ]);
            haveEat(&head[ i ], food);
            res = checkSelfCross(&head[ i ]);

            if(res == VICTORY && PLAYERS == 2) {
                switch(i) {
                case 0:
                    res = PLR_1_WIN;
                    break;
                case 1:
                    res = PLR_2_WIN;
                    break;
                }
            }
            else   if(res == GAME_OVER && PLAYERS == 2) {
                switch(i) {
                case 0:
                    res = PLR_2_WIN;
                    break;
                case 1:
                    res = PLR_1_WIN;
                    break;
                }
            }


            timeout(100);
            changeDirection(&head[ i ], key_pressed, i);
        }
        refreshFood(food, SEED_NUMBER);// Обновляем еду
    }
    return res;
}

void startMenu() {

    int max_x = 0, max_y = 0;
    int width = 50, height = 6;
    char c = 0;
    getmaxyx(stdscr, max_y, max_x);
    WINDOW *menu = newwin(height, width, max_y/2 - height/2, max_x/2 - width/2);
    box(menu,0,0);

    refresh();
    wrefresh(menu);

    mvprintw(max_y/2 - 1, max_x/2 - width/2 + 5, "Press '1' for SINGLE PLAYER");
    mvprintw(max_y/2, max_x/2 - width/2 + 5, "Press '2' for TWO PLAYERS");

    wrefresh(menu);
    do {
        c = getch();
    }
    while( c!= '1' && c!='2' );

    switch(c) {
    case '1':
        PLAYERS = 1;
        break;
    case '2':
        PLAYERS = 2;
        break;
    default:
        PLAYERS = 1;
    }

    wborder(menu, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    mvprintw(max_y/2 - 1, max_x/2 - width/2 + 5, "                            ");
    mvprintw(max_y/2, max_x/2 - width/2 + 5, "                         ");
    wrefresh(menu);
    delwin(menu);
    refresh();
}

void init_game(snake_t *head, food_t *food) {

    for(uint8_t i = 0; i < PLAYERS; i++) {
        initSnake( &head[ i ], START_TAIL_SIZE, 10 * (i + 1), 10 * (i + 1) );
    }
    initFood(food, MAX_FOOD_SIZE);
    putFood(food, SEED_NUMBER);// Кладем зерна
}

void init_screen() {

    initscr();
    keypad(stdscr, TRUE); // Включаем F1, F2, стрелки и т.д.
    raw();                // Откдючаем line buffering
    noecho();            // Отключаем echo() режим при вызове getch

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_CYAN, COLOR_BLACK);

    curs_set(FALSE);    //Отключаем курсор
    timeout(0);    //Отключаем таймаут после нажатия клавиши в цикле
    mvprintw(0, 5, "Movement: ARROWS for PLAYER 1; WSAD for PLAYER 2. Eat %d '$' for VICTORY! Press 'F10' for EXIT", VIC_COUNT);

}

int main()
{
    init_screen();
    startMenu();

    snake_t *snake = ( snake_t* ) malloc( PLAYERS * sizeof( snake_t ) );
    food_t *food = ( food_t* ) malloc( MAX_FOOD_SIZE * sizeof( food_t ) );
    int32_t game_result = 0;

    init_game(snake, food);
    game_result = update(snake, food);
    end_game(game_result);

    for(uint8_t i = 0; i < PLAYERS; i++) {
        free(snake[ i ].tail);
    }
    free(snake);
    endwin(); // Завершаем режим curses mod
    return 0;
}
