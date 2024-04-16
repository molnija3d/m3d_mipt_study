#include <stdio.h>
#include <inttypes.h>

 int main(void)
 {
   int32_t a,d1,d2,d3,mx;

   scanf("%d",&a);

   d1 = a%10;
   d2 = (a/10) % 10;
   d3 = (a/100) % 10;

   mx = d1 > d2 ? d1:d2;
   mx = mx > d3 ? mx:d3;

   printf("%d\n",mx);
 return 0;
 }
