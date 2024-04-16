#include <stdio.h>
#include <inttypes.h>

 int main(void)
 {
   int32_t a,b,c,d,e,mx;
   scanf("%d%d%d%d%d",&a,&b,&c,&d,&e);
   mx = a > b ? a:b;
   mx = mx > c ? mx:c;
   mx = mx > d ? mx:d;
   mx = mx > e ? mx:e;  
   printf("%d\n",mx);
 return 0;
 }
