#include <stdio.h>
#include <inttypes.h>
/*Организовать ввод натурального числа с клавиатуры. Программа должна определить наименьшую и наибольшую цифры, которые входят в состав данного натурального числа.*/

int main(void)
{
    int32_t a, d, mn=9, mx=0;
    scanf("%"SCNd32,&a);
    do
    {
        d = a%10;
        if (mn > d) mn = d;
        if (mx < d) mx = d;
    } 
    while(a/=10);
    
    printf("%"PRId32" %"PRId32"\n",mn,mx);

    return 0;
}
