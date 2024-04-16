#include <stdio.h>
#include <inttypes.h>

 int main(void)
 {
   int32_t a,b,c,mx;
   scanf("%d%d%d",&a,&b,&c);
   mx = a > b ? a:b;
   mx = mx > c ? mx:c;  
   printf("%d\n",mx);
 return 0;
 }
