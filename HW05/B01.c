#include <stdio.h>
#include <inttypes.h>


int main(void)
{
    int32_t a;
    scanf("%"SCNd32,&a);
    for(int i=1;i<=a;i++)
    {
      printf("%"PRId32" %"PRId32" %"PRId32"\n",i,i*i,i*i*i);    
    }
    
    return 0;
}
