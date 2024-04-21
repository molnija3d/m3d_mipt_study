#include <stdio.h>
#include <inttypes.h>


int main(void)
{
    int32_t a, odd=0, even=0;
    scanf("%"SCNd32,&a);
    do
    {
        (a%2)?++odd:++even;
    } 
    while(a/=10);
    
    printf("%"PRId32" %"PRId32"\n",even,odd);

    return 0;
}
