#include <stdio.h>
#include <inttypes.h>

 int main(void)
 {
   int32_t a,b;
   scanf("%d%d",&a,&b);
   if (a>b)
       printf("%d %d\n",b,a);
   else
       printf("%d %d\n",a,b);
 return 0;
 }
