#include <stdio.h>
#include <inttypes.h>
/*Составить функцию, печать всех простых множителей числа. Использовать ее для печати всех простых множителей числа.
void print_simple(int n)*/

void print_simple(int32_t n);
_Bool issimple(int32_t n);
int main(void)
{
    int32_t n;
    scanf("%d"SCNd32,&n);
    print_simple(n);
    return 0;
}

void print_simple(int32_t n)
{
  int32_t i=2;
  while(i*i < n+1)
  {
    if(n%i == 0 && issimple(i))
      {
       n /= i;
       printf("%"PRId32" ",i);
       i=1;
      }
    ++i;
  }
  printf("%"PRId32"\n",n);   
}

_Bool issimple(int32_t n)
{ 
    if(n == 2 || n == 3 || n == 5 || n == 7 || n == 9 || n == 11) 
       return 1;
    
    for(int32_t i=2; i*i < n+1; i++)
      if(n%i == 0)
        return 0;
    
    return 1;
}
