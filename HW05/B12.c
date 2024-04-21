#include <stdio.h>
#include <inttypes.h>


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
