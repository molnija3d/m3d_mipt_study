/*
Уравнение прямой
Определить уравнение прямой по координатам двух точек. Уравнение вида y=k*x+b
Input format
Четыре целых числа через пробел. Координаты X1 Y1 X2 Y2
Output format
Два числа K,B в формате "%.2f %.2f"
*/
#include <stdio.h>
#include <inttypes.h>

 int main(void)
 {
   int32_t x1,y1,x2,y2;
   float a,b;

   scanf("%"SCNd32"%"SCNd32"%"SCNd32"%"SCNd32,&x1,&y1,&x2,&y2);

   a = (float)(y1-y2)/(x1-x2);
   b =  y1 - a*x1; 

   printf("%.2f %.2f\n",a,b);
 return 0;
 }
