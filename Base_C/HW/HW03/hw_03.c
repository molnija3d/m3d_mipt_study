/*
Сумма трех чисел
Ввести три числа, найти их сумму.
Input format
Три целых числа
Output format
Строка вида %d+%d+%d=%d
*/
#include <stdio.h>

 int main(void)
 {
   int a,b,c;
   scanf("%d%d%d",&a,&b,&c);
   printf("%d+%d+%d=%d",a,b,c,a+b+c);
 return 0;
 }
