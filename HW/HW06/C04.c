#include <stdio.h>
#include <inttypes.h>
/*
Описать функцию вычисления f(x) по формуле:
f(x)= x*x при -2 ≤ x < 2;
x*x+4x+5 при x ≥ 2;
4 при x < -2.
Используя эту функцию для n заданных чисел, вычислить f(x). Среди вычисленных значений найти наибольшее.
*/

int32_t func(int32_t x);

int main(void)
{
    int32_t x,mx=0,res;

    scanf("%"SCNd32,&x);
    while(x!=0)
    {
        res = func(x);
        if (mx < res) mx = res;

        scanf("%"SCNd32,&x);
    }
    printf("%"PRId32"\n",mx);
    return 0;
}

int32_t func(int32_t x)
{
    if(x < -1)
        return 4;
    if(x < 2)
        return x*x;
    return  x*x + 4*x + 5;
}
