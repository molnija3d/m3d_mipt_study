#include <stdio.h>
#include <inttypes.h>


void changeSign(float *f)
{
        union {
                float f;
                uint32_t u;
        } tmp;

        tmp.f = *f;
        tmp.u = tmp.u ^ 0x80000000;
        *f = tmp.f;
}

int main(void)
{
 float a;
  a = -1.6;
  printf("%f\n", a);
  changeSign(&a);
  printf("%f\n", a);
  printf("%x\n", 0x80000000);
  printf("%x\n", 1 << 31);
  printf("%x\n", 1 << 31 | 1 << 30 | 1 << 20);
 return 0;
}
