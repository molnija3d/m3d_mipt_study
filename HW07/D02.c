#include <stdio.h>
#include <inttypes.h>
/*
Составить рекурсивную функцию, печать всех чисел от 1 до N
*/
void r_print(int32_t n);
int main(void)
{
    int32_t n;
    scanf("%"SCNd32,&n);
    r_print(n);
    return 0;
}

void r_print(int32_t n)
{
    if(n>1)
       r_print(n-1);
    printf("%"PRId32" ",n);
}
