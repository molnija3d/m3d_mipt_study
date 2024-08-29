#include <stdio.h>
#include <inttypes.h>
/*
Перевести натуральное число в двоичную систему счисления. Необходимо реализовать рекурсивную функцию.
*/
void r_dtob(int32_t n);

int main(void)
{
    int32_t n;
    scanf("%"SCNd32,&n);
    (n > 0) ? r_dtob(n) : printf("0");
    return 0; 
}

void r_dtob(int32_t n)
{
    if(n)
      {
        r_dtob(n/2);  
        printf("%"PRId32,n%2);  
      }
}
