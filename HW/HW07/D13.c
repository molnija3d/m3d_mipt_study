#include <stdio.h>
#include <inttypes.h>
/*
Составить рекурсивную функцию, печать всех простых множителей числа.
*/
void r_prmul(int32_t n);

int main(void)
{
    int32_t n;
    scanf("%"SCNd32,&n);
    r_prmul(n);
    return 0;
}

void r_prmul(int32_t n)
{
    static int32_t div = 2;
    if(n!=1)
    {
        if(n%div == 0)
        {
            printf("%d ",div);
            r_prmul(n/div);
        }
        else
        {
            ++div;
            r_prmul(n);
        }
    }
}
