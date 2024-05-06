/*
Сумма максимума и минимума
Напечатать сумму максимума и минимума.
Input format
Пять целых чисел через пробел
Output format
Одно целое число - сумма максимума и минимума
*/
#include <stdio.h>
#include <inttypes.h>

 int main(void)
 {
   int32_t a,b,c,d,e,mn,mx;
   scanf("%"SCNd32"%"SCNd32"%"SCNd32"%"SCNd32"%"SCNd32,&a,&b,&c,&d,&e);

   if (a>b)
   {
       mx = a;
       mn = b;
   }  
   else
   {
       mn = a;
       mx = b;
   }

   mn = mn < c ? mn : c;
   mx = mx > c ? mx : c;
   
   mn = mn < d ? mn : d;
   mx = mx > d ? mx : d;
   
   mn = mn < e ? mn : e;
   mx = mx > e ? mx : e;
   
   printf("%"PRId32"\n",mn+mx);
 return 0;
 }
