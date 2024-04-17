#include <stdio.h>
#include <inttypes.h>

 int main(void)
 {
   int32_t a,b,c;

   scanf("%"SCNd32"%"SCNd32"%"SCNd32,&a,&b,&c);
   (a<b && b<c)? printf("YES\n"): printf("NO\n");
   
 return 0;
 }
