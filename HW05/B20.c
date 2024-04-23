#include <stdio.h>
#include <inttypes.h>
/*Проверить число на простоту.*/

int main(void)
{
    int32_t a,i=1;

    scanf("%"SCNd32,&a);
    if(a>3)
      while(i*i < a)
        {
           i++;
           if(a%i == 0)
             {
               printf("NO\n");
               return 0;
             }
         }
     (a>1)? printf("YES\n"):printf("NO\n");
    return 0;
}
