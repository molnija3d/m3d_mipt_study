#include <stdio.h>
#include <inttypes.h>
/*Составить функцию, модуль числа и привести пример ее использования.*/
int32_t module(int32_t a);

int main(void)
{
    int32_t a;
    
    scanf("%"SCNd32,&a);
    printf("%"PRId32"\n",module(a));
    
    return 0;
}

int32_t module(int32_t a)
{
    if (a > 0) return a;
    return -a;
}
