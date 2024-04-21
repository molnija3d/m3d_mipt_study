#include <stdio.h>
#include <inttypes.h>

int main(void)
{
    int32_t n,cur=1,prev=0,tmp;

    scanf("%"SCNd32,&n);

    do
    {
        printf("%"PRId32" ",cur);
        tmp = cur;
        cur += prev;
        prev = tmp;
    }
    while (--n);
    
    return 0;
}

