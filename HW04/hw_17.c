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
