#include <stdio.h>
#include <inttypes.h>


int main(void)
{
    int32_t a,cnt=0;
    scanf("%"SCNd32,&a);
    do
    {
        if(a%10==9)
          ++cnt;
    }
    while(a/=10);
    (cnt == 1)? printf("YES\n"):printf("NO\n");

    return 0;
}
