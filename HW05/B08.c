#include <stdio.h>
#include <inttypes.h>
/*
Ввести целое число и определить, верно ли, что в нём ровно одна цифра «9».
*/

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
    printf((cnt == 1)? "YES\n":"NO\n");

    return 0;
}
