#include <stdio.h>
#include <inttypes.h>


int main(void)
{
    int32_t a,sum=0;
    scanf("%"SCNd32,&a);
    do
    {
     sum += a%10;
    }
    while(a/=10);
    printf("%"PRId32"\n",sum);
    
    return 0;
}
