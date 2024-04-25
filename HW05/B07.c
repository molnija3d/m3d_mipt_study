#include <stdio.h>
#include <inttypes.h>
/*
Ввести целое число и определить, верно ли, что в его записи есть две одинаковые цифры, НЕ обязательно стоящие рядом.
*/

int main(void)
{
    int32_t a,tmp,d1,d2;
    scanf("%"SCNd32,&a);
    tmp = a;
    d1 = a%10;
    while(tmp/=10)
    {
        while(a/=10)
        {
            d2 = a%10;
            if (d1 == d2)
            {
                printf("YES\n");
                return 0;
            }
        }
        d1 = tmp%10;
    }
    printf("NO\n");
    return 0;
}
