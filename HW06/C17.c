#include <stdio.h>
#include <inttypes.h>
/*
Составить логическую функцию, которая определяет, верно ли, что в заданном числе сумма цифр равна произведению.
int is_happy_number(int n)
 */

int32_t is_happy_number(int32_t a);
int32_t sum(int32_t a);
int32_t mul(int32_t a);

int main(void)
{
    int32_t a;
    scanf("%"SCNd32,&a);
    printf("%s\n",(is_happy_number(a))? "YES" : "NO");
    return 0;
}


int32_t is_happy_number(int32_t a)
{
    if (sum(a) == mul(a))
       return 1;
    return 0;
}
    
int32_t sum(int32_t a)
{
  int32_t sum=0;
  do
  {
    sum += a%10;  
  } 
  while (a/=10);
  return sum;  
}

int32_t mul(int32_t a)
{
  int32_t mul=1;
  do
  {
    mul *= a%10;  
  } 
  while (a/=10);
  return mul;    
}
