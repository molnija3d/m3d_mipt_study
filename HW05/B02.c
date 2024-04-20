#include <stdio.h>
#include <inttypes.h>


int main(void)
{
    int32_t a,b;
    scanf("%"SCNd32"%"SCNd32,&a,&b);
    for(int i=a;i<=b;i++)
    {
      printf("%"PRId32" ",i*i);    
    }
    
    return 0;
}
