#include <stdio.h>
#include <inttypes.h>
/*Составить функцию, которая переводит число N из десятичной системы счисления в P-ичную систему счисления.*/
int32_t conv(int32_t n,int32_t p);

int main(void)
{
    int32_t n,p;
     
    scanf("%"SCNd32" %"SCNd32,&n,&p);
    printf("%"PRId32"\n",conv(n,p)) ;
    return 0;
}

int32_t conv(int32_t n, int32_t p)
{
    uint32_t res = 0;
    for(uint32_t i = 1;n;i*=10, n/=p)
    {
        res += n%p*i;
    }
    return  res;
}
