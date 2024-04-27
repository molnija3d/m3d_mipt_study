#include <stdio.h>
/*
Дано натуральное число N. Вычислите сумму его цифр. Необходимо составить рекурсивную функцию.
int sum_digits(int n)
*/
int sum_digits(int n);

int main(void)
{
    int n;
    scanf("%d",&n);
    printf("%d\n",sum_digits(n));
    return 0; 
}

int sum_digits(int n)
{
  int sum = n%10;  
  if(n>0)
   return sum + sum_digits(n/10);
  return 0;
}
