#include <stdio.h>
#include <inttypes.h>

int main(void) {
    float a = 0;
    printf("Enter float value:");
    scanf("%f", &a);
    uint32_t m, e, bits = *(uint32_t *)&a;
    e = (bits >> 23) & 0xff;
    m  = bits & 0x7fffff ;
    printf("m = %d, e = %d k = %d\n", m, e, bits);

    return 0;
}
