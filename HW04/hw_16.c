#include <stdio.h>
#include <inttypes.h>

 int main(void)
 {
   int32_t a,b,c;

   scanf("%d%d%d",&a,&b,&c);
   (a<b && b<c)? printf("YES\n"): printf("NO\n");
   
 return 0;
 }
