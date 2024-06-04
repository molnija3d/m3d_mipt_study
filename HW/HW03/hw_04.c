/*
Сумма и произведение трех чисел
Ввести три числа, найти их сумму и произведение.
Input format
Три целых числа через пробел.
Output format
Строка вида
%d+%d+%d=%d
%d*%d*%d=%d
*/
#include <stdio.h>

 int main(void)
 {
   int a,b,c;
   scanf("%d %d %d",&a,&b,&c);
   printf("%d+%d+%d=%d\n",a,b,c,a+b+c);
   printf("%d*%d*%d=%d\n",a,b,c,a*b*c);
 return 0;
 }
