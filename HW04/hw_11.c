#include <stdio.h>
#include <inttypes.h>

 int main(void)
 {
   int32_t a,b,c,d,e,mn,mx;
   scanf("%d%d%d%d%d",&a,&b,&c,&d,&e);

   if (a>b)
   {
       mx = a;
       mn = b;
   }  
   else
   {
       mn = a;
       mx = b;
   }

   mn = mn < c ? mn : c;
   mx = mx > c ? mx : c;
   
   mn = mn < d ? mn : d;
   mx = mx > d ? mx : d;
   
   mn = mn < e ? mn : e;
   mx = mx > e ? mx : e;
   
   printf("%d\n",mn+mx);
 return 0;
 }
