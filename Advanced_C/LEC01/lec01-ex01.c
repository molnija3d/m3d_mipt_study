#include <stdio.h>
#include <inttypes.h>

int main(void)
{
    int32_t a, a2, sign, sign2;
    scanf("%d",&a);
    printf("a hex: %x\n",a);
    a2 = a;
    sign = a >> 31;
    sign2 = 0xFFFFFFFF;
    a2 = (a2^sign2) + 1;
    a ^= sign;
    a += sign & 0x1;
    printf("a:%x a2: %x\n", a, a2);
    printf("sign hex: %x %x\n",sign, sign2);
    printf("sign dec: %8d %d\n",sign, sign2);
    return 0;
}
