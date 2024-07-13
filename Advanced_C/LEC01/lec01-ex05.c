#include <stdio.h>
#include <inttypes.h>


_Bool difSign(int32_t a, int32_t b)
{
 return (a >> 31) ^ (b >> 31); 
}

int main(void)
{
 int32_t a, b;
  scanf("%d %d", &a, &b);
  printf("%d\n", difSign(a, b));
 return 0;
}
