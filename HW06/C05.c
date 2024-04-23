#include <stdio.h>
#include <inttypes.h>
/*
Составить функцию, которая определяет сумму всех чисел от 1 до N и привести пример ее использования.
*/
int32_t sum(int32_t x);

int main(void)
{
    int32_t x;
     
    scanf("%"SCNd32,&x);
    printf("%"PRId32"\n",sum(x)) ;
    return 0;
}

int32_t sum(int32_t x)
{
    int32_t sum = 0;
    for(int i = 1; i <= x; ++i)
        sum += i;
    
    return  sum;
}
