#include <stdio.h>
#include <inttypes.h>
/*
Вывести на экран ряд чисел Фибоначчи, состоящий из n элементов.
Числа Фибоначчи – это элементы числовой последовательности 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, …, 
в которой каждое последующее число равно сумме двух предыдущих.
*/

int main(void)
{
    int32_t n,cur=1,prev=0,tmp;

    scanf("%"SCNd32,&n);

    do
    {
        printf("%"PRId32" ",cur);
        tmp = cur;
        cur += prev;
        prev = tmp;
    }
    while (--n);
    
    return 0;
}

