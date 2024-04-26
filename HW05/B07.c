#include <stdio.h>
#include <inttypes.h>
/*
Ввести целое число и определить, верно ли, что в его записи есть две одинаковые цифры, НЕ обязательно стоящие рядом.
*/

int main(void)
{
    int32_t a,d1,d2;
    scanf("%"SCNd32,&a);
    d1 = a;
   do
    {
        a = d1;
        while(a/=10)
        {
            d2 = a%10;
            if ((d1%10) == d2)
            {
                printf("YES\n");
                return 0;
            }
        }
    }
    while(d1/=10);
    printf("NO\n");
    return 0;
}
