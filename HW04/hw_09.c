/*
Наибольшее из пяти чисел
Ввести пять чисел и найти наибольшее из них.
Input format
Пять целых чисел разделенных пробелом
Output format
Одно целое число
*/
#include <stdio.h>
#include <inttypes.h>

 int main(void)
 {
   int32_t a,b,c,d,e,mx;
   scanf("%"SCNd32"%"SCNd32"%"SCNd32"%"SCNd32"%"SCNd32,&a,&b,&c,&d,&e);
   mx = a > b ? a:b;
   mx = mx > c ? mx:c;
   mx = mx > d ? mx:d;
   mx = mx > e ? mx:e;  
   printf("%"PRId32"\n",mx);
 return 0;
 }
