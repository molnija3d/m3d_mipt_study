#include <stdio.h>
#include <inttypes.h>
/*
Дано натуральное число N. Посчитать количество «1» в двоичной записи числа. Составить рекурсивную функцию.
*/
int32_t r_sum1(int32_t n);

int main(void)
{
    int32_t n;
    scanf("%"SCNd32,&n);
    printf("%"PRId32"\n",r_sum1(n));
    return 0;
}

int32_t r_sum1(int32_t n)
{
    static int32_t sum=0;
    if(n)
    {
        sum = r_sum1(n/2);
        if(n%2)
            return ++sum;
    }
    return sum;
}