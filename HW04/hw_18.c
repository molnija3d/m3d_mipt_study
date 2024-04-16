#include <stdio.h>
#include <inttypes.h>

 int main(void)
 {
   int32_t a,b;

   scanf("%d%d",&a,&b);
 
   if (a == b) 
      printf("Equal\n");
   else if (a > b)
      printf("Above\n");
   else
      printf("Less\n");  
 return 0;
 }
