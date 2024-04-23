#include <stdio.h>
#include <inttypes.h>
/*Ввести целое число и определить, верно ли, что в нём ровно 3 цифры.*/

int main(void)
{
    int32_t a,cnt=0;
    scanf("%"SCNd32,&a);
    do
    {
     cnt++;
    }
    while(a/=10);
    (cnt == 3)? printf("YES"):printf("NO");
    
    return 0;
}
