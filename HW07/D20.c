#include <stdio.h>
#include <inttypes.h>
/*
Написать рекурсивную функцию возведения целого числа n в степень p.
int recurs_power(int n, int p)
Используя данную функцию, решить задачу.
*/
int recurs_power(int n, int p);

int main(void)
{
    int n,p;
    scanf("%d %d",&n,&p);
    printf("%d\n",recurs_power(n,p));
    return 0;
}

int recurs_power(int n, int p)
{
    if(p == 0)
        return 1;
    return n*recurs_power(n, p-1);
}
