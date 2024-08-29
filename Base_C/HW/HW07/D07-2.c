#include <stdio.h>
#include <inttypes.h>
/*
Составить рекурсивную функцию, печать всех чисел от N до 1.
*/
void r_printn(int32_t n);

int main(void)
{
    int32_t n;
    scanf("%"PRId32,&n);
    r_printn(n);
    return 0; 
}

void r_printn(int32_t n)
{
    if(n > 1)
      {
        
        r_printn(--n);
         printf("%"PRId32" ",n);  
      }
     
      
}
