#include <stdio.h>
#include <inttypes.h>

int32_t NOD(int32_t a,int32_t b);
int main(void)
{
    int32_t a,b;
    scanf("%"SCNd32"%"SCNd32,&a,&b);
    printf("%"PRId32"\n",NOD(a,b));
    return 0;
}

int32_t NOD(int32_t a,int32_t b)
{
    if (b==0)
       return a;
    return NOD(b, a%b);
}