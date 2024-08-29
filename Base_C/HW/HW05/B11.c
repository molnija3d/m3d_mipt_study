#include <stdio.h>
#include <inttypes.h>
/*
Ввести целое число и «перевернуть» его, так чтобы первая цифра стала последней и т.д.
*/

int main(void)
{
    int32_t a,b=0;
    scanf("%"SCNd32,&a);
    
    do
    {
        b = b*10 + a%10;
    } 
    while(a/=10);
    printf("%"PRId32"\n",b);

    return 0;
}
