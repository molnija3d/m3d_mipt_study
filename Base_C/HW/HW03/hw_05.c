/*
Среднее арифметическое трех чисел
Ввести три числа, найти их среднее арифметическое.
Input format
Три целых числа
Output format
Вещественное число в формате %.2f
*/
#include <stdio.h>

 int main(void)
 {
   int a,b,c;
   scanf("%d %d %d",&a,&b,&c);
   printf("%.2f",(a+b+c)/3.);
 return 0;
 }
