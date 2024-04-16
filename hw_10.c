#include <stdio.h>
#include <inttypes.h>

 int main(void)
 {
   int32_t a,b,c,d,e,mn;
   scanf("%d%d%d%d%d",&a,&b,&c,&d,&e);
   mn = a < b ? a:b;
   mn = mn < c ? mn:c;
   mn = mn < d ? mn:d;
   mn = mn < e ? mn:e;  
   printf("%d\n",mn);
 return 0;
 }
