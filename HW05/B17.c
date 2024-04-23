#include <stdio.h>
#include <inttypes.h>
/*
Ввести натурально число и напечатать все числа от 10 до введенного числа - у которых сумма цифр равна произведению цифр
*/

int32_t sum(int32_t a);
int32_t mul(int32_t a);

int main(void)
{
    int32_t a,tmp = 9;

    scanf("%"SCNd32,&a);

    while (tmp++ < a)
        if(sum(tmp) == mul(tmp))
           printf("%"PRId32" ",tmp);
    
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
