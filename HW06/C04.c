#include <stdio.h>
#include <inttypes.h>

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
