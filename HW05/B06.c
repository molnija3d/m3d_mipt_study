#include <stdio.h>
#include <inttypes.h>


int main(void)
{
    int32_t a,d1,d2;
    scanf("%"SCNd32,&a);
    d1 = a%10;
    while(a/=10)
    {
     d2 = a%10;
     if (d1 == d2) 
     {
         printf("YES\n");
         return 0;
     }
     d1 = d2;
    }
    printf("NO\n");    
    return 0;
}
