/*
Наибольшее из трех чисел
Ввести три числа и найти наибольшее из них
Input format
Три целых числа через пробел
Output format
Одно наибольшее целое число
*/
#include <stdio.h>
#include <inttypes.h>

 int main(void)
 {
   int32_t a,b,c,mx;
   scanf("%"SCNd32"%"SCNd32"%"SCNd32,&a,&b,&c);
   mx = a > b ? a:b;
   mx = mx > c ? mx:c;  
   printf("%"PRId32"\n",mx);
 return 0;
 }
