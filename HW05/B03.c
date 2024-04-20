#include <stdio.h>
#include <inttypes.h>


int main(void)
{
    int32_t a,b,sum=0;
    scanf("%"SCNd32"%"SCNd32,&a,&b);
    for(int i=a;i<=b;i++)
    {
      sum+=i*i;
    }
    printf("%"PRId32" ",sum);
    
    return 0;
}
