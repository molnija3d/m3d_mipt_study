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
int32_t count_res(int32_t *res, int32_t n);


int32_t main() {
    int32_t n = 0, anum[100] = {0};
    n = getnumbers(anum);
    n = count_nums(anum, n);
    printf("%d\n", n);

    return 0;
}


int32_t count_nums(int32_t *anum, int32_t n) {
    int32_t c = 0, j = 0, res[10000] = {0};
    int8_t d1 = 0, d2 = 0, d3 = 0;
    for(int32_t i1 = 0; i1 < n - 2; i1++) {
        d1 = anum[i1];
        for(int32_t i2 = i1 + 1; i2 < n - 1; i2++) {
            d2 = anum[i2];
            for(int32_t i3 = i2 + 1; i3 < n; i3++) {
                d3 = anum[i3];
                res[j++] = d1 * 100 + d2 * 10 + d3;
            }
        }
    }

    return count_res(res, j);
}

int32_t count_res(int32_t *res, int32_t n) {
    for(int32_t i = 0; i < n; i++) {
        int32_t val = res[i];
        for(int32_t j = i + 1; j < n; j++) {
            if (val == res[j]) {
                res[j] = -1;
            }
        }
    }
    int32_t cnt = 0;
    for(int32_t i = 0; i < n; i++) {
        if(res[i] >= 0) {
            cnt++;
        }
    }
    return cnt;
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


