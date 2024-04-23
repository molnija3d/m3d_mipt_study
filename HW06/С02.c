#include <stdio.h>
#include <inttypes.h>

int32_t power(int32_t n,int32_t p);

int main(void)
{
    int32_t n,p;
    
    scanf("%"SCNd32" %"SCNd32,&n,&p);
    printf("%"PRId32"\n",power(n,p));
    
    return 0;
}

int32_t power(int32_t n,int32_t p)
{
    int32_t pow=n, i=1;
    if(p == 0) 
       return 1;
 
    while (i++< p)
    {
        pow*=n;
    }
 
    return pow;
}
