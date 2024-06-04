/*
Какое время года
Ввести номер месяца и вывести название времени года.
Input format
Целое число от 1 до 12 - номер месяца.
Output format
Время года на английском: winter, spring, summer, autumn
*/
#include <stdio.h>
#include <inttypes.h>

 int main(void)
 {
   int32_t a;

   scanf("%"SCNd32,&a);
 
   if (a > 11 || a < 3) 
      printf("winter\n");
   else if (a < 6)
      printf("spring\n");
   else if (a < 9)
      printf("summer\n");
   else
      printf("autumn\n");   
 return 0;
 }
