/*
 * Задача 5-2-Префикс и суфикс
На стандартном потоке ввода задаются две символьные строки, разделённые символом перевода строки. Каждая из строк не превышает по длине 104. В строках не встречаются пробельные символы.
На стандартный поток вывода напечатайте два числа, разделённых пробелом: первое число — длина наибольшего префикса первой строки, являющегося суффиксом второй; второе число — наоборот, длина наибольшего суффикса первой строки, являющегося префиксом второй. Сравнение символов проводите с учётом регистра (т.е. символы 'a' и 'A' различны).
*/
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#define LEN 104
#define min(a,b) (a < b ? a : b)

void zFunction(char *str, int32_t z[]);
void zFunction2(char *str, int32_t z[]);
void zPrint(int32_t z[], int32_t n);
void zPrintFull(int32_t z[], int32_t n);
void zZero(int32_t z[], int32_t n);
//int32_t min(int32_t a, int32_t b);

int32_t main() {
    char inp[LEN], pref[LEN], str[2*LEN+1];
    int32_t z[2*LEN] = {0}, n = 0;
    scanf("%s", inp);
    scanf("%s", pref);

    sprintf(str,"%s#%s",inp, pref);
    zFunction(str, z);
    n = strlen(str);
    zPrint(z, n);
    zZero(z,n);

    sprintf(str,"%s#%s",pref, inp);
    zFunction(str, z);
    zPrint(z, strlen(str));

    printf("\n");
    return 0;
}

void zZero(int32_t z[], int32_t n) {
    for(int32_t i = 0; i < n; i++) {
        z[i] = 0;
    }
}
void zPrintFull(int32_t z[], int32_t n) {

    int8_t res = 0;
    for(int32_t i = 1; i < n; i++) {
            printf("%"PRId32" ", z[i]);
    }
        printf("\n");
}

void zPrint(int32_t z[], int32_t n) {

    int8_t res = 0;
    for(int32_t i = 1; i < n; i++) {
        if(z[i] == n - i) {
            printf("%"PRId32" ", z[i]);
            res = 1;
        }
    }
    if(!res) {
        printf("0 ");
    }
}

void zFunction2(char *str, int32_t z[]) {
    int32_t i = 0, l = 0;
    int32_t len = (int32_t) strlen(str);
    for(int32_t i = 1; i < len; i++) {
        z[i] = min(z[i-l], l + z[l] - i);
        if(z[i] < 0) {
            z[i] = 0;
        }
        while(i + z[i] < len && str[z[i]] == str[z[i] + i]) {
            z[i]++;
        }
        if(i + z[i] > l + z[l])
        {
            l = i;
        }

    }
}

void zFunction(char *str, int32_t z[]) {
    int32_t i = 0, l = 0, r = 0;
    int32_t len = (int32_t) strlen(str);
    for(int32_t i = 1; i < len; i++) {
        if(i <= r)
        {
            z[i] = min(z[i - l], r - i);
        }
        while(i + z[i] < len && str[z[i]] == str[z[i] + i]) {
            z[i]++;
        }
        if(i + z[i] > r)
        {
            l = i;
            r = i + z[i];
        }

    }
}

/*
int32_t min(int32_t a, int32_t b)
{
    return a < b ? a:b;

}
*/

