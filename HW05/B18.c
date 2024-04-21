#include <stdio.h>
#include <inttypes.h>

int32_t sum(int32_t a);
int32_t mul(int32_t a);

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

