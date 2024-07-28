/*
Задача 5-1-Вычеркивание
Сколько различных трехзначных чисел можно получить из заданного натурального N, вычеркивая цифры из его десятичной записи?
Формат данных на входе: Единственное натуральное число N.
Формат данных на выходе: Единственное целое число – найденное количество.

Пример №1
Данные на входе:		1111111111111111111111111
Данные на выходе:	1


Пример №1
Данные на входе:		1111122222
Данные на выходе:	4


Пример №1
Данные на входе:		9876543210
Данные на выходе:	120
*/
#include <stdio.h>
#include <inttypes.h>

int32_t getnumbers(int32_t *anum);
void printarr(int32_t *anum, int32_t n);
int32_t count_nums(int32_t *anum, int32_t n);


int32_t main() {
    int32_t n = 0, anum[100] = {0};
    n = getnumbers(anum);
    printarr(anum, n);

    return 0;
}


int32_t count_nums(int32_t *anum, int32_t n) {
    int32_t c = 0;

    return n;
}


int32_t getnumbers(int32_t *anum) {
    int32_t n = 0, num;
    char c = 0;
    while((c = getchar()) != '\n') {
        num = c - 0x30;
        if(num >= 0 && num < 10) {
            anum[n++] = num;
        }
    }
    return n;
}


void printarr(int32_t *anum, int32_t n) {
    for(int32_t i = 0; i < n; i++) {
        printf("%d", anum[i]);
    }
    printf("\n");
}


