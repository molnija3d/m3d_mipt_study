/*
Above, less, equal
Ввести два числа. Если первое число больше второго, то программа печатает слово Above. Если первое число меньше второго, то программа печатает слово Less. А если числа равны, программа напечатает сообщение Equal.
Input format
Два целых числа
Output format
Одно единственное слово: Above, Less, Equal
*/
#include <stdio.h>
#include <inttypes.h>

 int main(void)
 {
   int32_t a,b;

   scanf("%"SCNd32"%"SCNd32,&a,&b);
 
   if (a == b) 
      printf("Equal\n");
   else if (a > b)
      printf("Above\n");
   else
      printf("Less\n");  
 return 0;
 }
