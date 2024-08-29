/*
Максимальная цифра
Дано трехзначное число, напечатать макисмальную цифру
Input format
Целое положительное трехзначное число
Output format
Одна цифра
*/
#include <stdio.h>
#include <inttypes.h>

 int main(void)
 {
   int32_t a,d1,d2,d3,mx;

   scanf("%"SCNd32,&a);

   d1 = a%10;
   d2 = (a/10) % 10;
   d3 = (a/100) % 10;

   mx = d1 > d2 ? d1:d2;
   mx = mx > d3 ? mx:d3;

   printf("%"PRId32"\n",mx);
 return 0;
 }
