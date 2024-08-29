#include <stdio.h>
#include <inttypes.h>
/*
Составить рекурсивную функцию, которая определяет сумму всех чисел от 1 до N
*/
int32_t r_sum(int32_t n);
int main(void)
{
    int32_t n;
    scanf("%"SCNd32,&n);
    printf("%"PRId32"\n",r_sum(n));
    return 0;
}

int32_t r_sum(int32_t n)
{
  
    if(n)
     return n+r_sum(n-1);
    return 0;
}
