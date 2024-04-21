#include <stdio.h>
#include <inttypes.h>


int main(void)
{
    int32_t a, b, NOD;

    scanf("%"SCNd32"%"SCNd32,&a,&b);
    if(a%b == 0)
    {
        printf("%"PRId32"\n",b);
        return 0;
    }
    while(a>1)
    {
        if(a>b)
        {
            NOD = a-b;
            a = NOD;
            if(b%NOD == 0)
               a=1;
        }
        else
        {
            NOD = b-a;
            b = NOD;
            if(a%NOD == 0)
               a=1;
        }
    }

    printf("%"PRId32"\n",NOD);
    return 0;
}
