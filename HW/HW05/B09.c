#include <stdio.h>
#include <inttypes.h>
/*
Ввести целое число и определить, верно ли, что все его цифры четные.
*/

int main(void)
{
    int32_t a;
    scanf("%"SCNd32,&a);
    do
    {
        if(( a%10)%2)
        {
          printf("NO\n");
          return 0;  
        }
    }
    while(a/=10);
    printf("YES\n");

    return 0;
}
