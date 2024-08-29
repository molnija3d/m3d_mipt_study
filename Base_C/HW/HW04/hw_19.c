/*
Существует ли треугольник
Даны стороны треугольника a, b, c. Определить существует ли такой треугольник.
Input format
Три целых числа. Стороны треугольника a, b, c.
Output format
YES или NO
*/
#include <stdio.h>
#include <inttypes.h>

 int main(void)
 {
   int32_t a,b,c;

   scanf("%"SCNd32"%"SCNd32"%"SCNd32,&a,&b,&c);
   ((a+b)>c)&&((a+c)>b)&&((c+b)>a)? printf("YES\n"): printf("NO\n");
 return 0;
 }
