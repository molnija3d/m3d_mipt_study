/*
Наибольшее из двух чисел
Ввести два числа и вывести их в порядке возрастания.
Input format
Два целых числа
Output format
Два целых числа
*/
#include <stdio.h>
#include <inttypes.h>

 int main(void)
 {
   int32_t a,b;
   scanf("%"SCNd32"%"SCNd32,&a,&b);
   if (a>b)
       printf("%"PRId32" %"PRId32"\n",b,a);
   else
       printf("%"PRId32" %"PRId32"\n",a,b);
 return 0;
 }
