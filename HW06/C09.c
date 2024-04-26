#include <stdio.h>
#include <inttypes.h>
/*
Составить функцию вычисления N!. Использовать ее при вычислении факториала
int factorial(int n)
*/
int32_t factorial(int32_t n);

int main(void)
{
    int32_t n;
    scanf("%d"SCNd32,&n);
    printf("%"PRId32"\n",factorial(n));
    return 0;
}

int32_t factorial(int32_t n)
{
    int32_t res = n;
    if (n>1)
        res *= factorial(n-1);
    return res;
}
