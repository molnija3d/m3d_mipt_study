#include <stdio.h>
#include <inttypes.h>


int main(void)
{
    int32_t a, cnt=0;
    
    scanf("%"SCNd32,&a);
    while(a!=0)
    {
        if(!(a%2))
			++cnt;
        scanf("%"SCNd32,&a);
    } 
    
    printf("%"PRId32"\n",cnt);

    return 0;
}
