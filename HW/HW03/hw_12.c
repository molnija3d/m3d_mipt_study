/*
Сумма цифр
На вход подается произвольное трехзначное число, напечать сумму цифр
Input format
Трехзначное целое положительное число
Output format
Одно целое число
*/
#include <stdio.h>

 int main(void)
 {
   int a;
   scanf("%d",&a);
   printf("%d",a%10 + (a/10)%10 + (a/100)%10);
 return 0;
 }