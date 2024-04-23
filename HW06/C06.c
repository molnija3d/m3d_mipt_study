#include <stdio.h>
#include <inttypes.h>
/*Необходимо составить функцию, которая определяет, сколько зерен попросил положить на N-ую клетку изобретатель шахмат (на 1-ую – 1 зерно, на 2-ую – 2 зерна, на 3-ю – 4 зерна, …)*/
uint64_t seeds(int32_t n);

int main(void)
{
    int32_t n;
     
    scanf("%"SCNd32,&n);
    printf("%"PRIu64"\n",seeds(n)) ;
    return 0;
}

uint64_t seeds(int32_t n)
{
    uint64_t res = 1;
    for(int i = 1; i < n; ++i)
        res *= 2;
    return  res;
}
